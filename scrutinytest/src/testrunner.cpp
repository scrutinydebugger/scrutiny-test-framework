//    testrunner.cpp
//        The class that will iterate all test suites and run the test cases
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-embedded)
//
//   Copyright (c) 2025 Scrutiny Debugger

#include "scrutinytest/testrunner.hpp"
#include "scrutinytest/testresult.hpp"
#include <iostream>

namespace scrutinytest
{
    uint32_t default_timestamp_ms_func()
    {
        return 0;
    }

    TestRunner *MainRunner::get()
    {
        static TestRunner main_runner;
        return &main_runner;
    }

    TestRunner::TestRunner() :
        m_ostream(&std::cout),
        m_test_cases(),
        m_init_error_str(),
        m_timestamp_ms_func(default_timestamp_ms_func),
        m_init_error(false),
        m_success(false)
    {
    }

    void set_ostream(std::ostream *stream);

    int TestRunner::run()
    {
        m_success = false;
        uint32_t run_start_timestamp_ms = m_timestamp_ms_func();
        if (m_init_error)
        {
            print_fatal(m_init_error_str);
            return 2;
        }

        unsigned long int error_count = 0;
        unsigned long int fail_count = 0;
        unsigned long int pass_count = 0;
        for (test_case_map_t::iterator it = m_test_cases.begin(); it != m_test_cases.end(); it++)
        {
            std::string const &suitename = it->first;
            std::vector<TestCase *> &testcases = it->second;
            *m_ostream << '\n';
            uint32_t testsuite_start_timestamp_ms = m_timestamp_ms_func();
            print_suite_start(suitename, testcases.size()) << std::endl;

            for (int i = 0; i < testcases.size(); i++)
            {
                uint32_t testcase_start_timestamp_ms = m_timestamp_ms_func();
                TestCase *testcase = testcases[i];
                TestResult result(*m_ostream);
                testcase->_set_result(&result);

                bool error = false;
                bool pass = false;
                std::string error_str;
#if SCRUTINYTEST_HAVE_EXCEPTIONS
                try
                {
#endif
                    print_run_start(suitename, testcase->name()) << std::endl;
                    testcase->SetUp();
#if SCRUTINYTEST_HAVE_EXCEPTIONS
                    try
                    {
#endif
                        testcase->body();
                        if (result.failure_count() == 0)
                        {
                            pass = true;
                        }
#if SCRUTINYTEST_HAVE_EXCEPTIONS
                    }
                    catch (std::exception const &e)
                    {
                        error = true;
                        error_str = e.what();
                    }
                    catch (std::string const &e)
                    {
                        error = true;
                        error_str = e;
                    }
                    catch (char const *e)
                    {
                        error = true;
                        error_str = e;
                    }
                    catch (...)
                    {
                        error = true;
                        error_str = "unknown error";
                    }
#endif
                    testcase->TearDown();
#if SCRUTINYTEST_HAVE_EXCEPTIONS
                }
                catch (const std::exception &e)
                {
                    if (!error)
                    {
                        error = true;
                        error_str = e.what();
                    }
                }
                catch (std::string const &e)
                {
                    if (!error)
                    {
                        error = true;
                        error_str = e;
                    }
                }
                catch (char const *e)
                {
                    if (!error)
                    {
                        error = true;
                        error_str = e;
                    }
                }
                catch (...)
                {
                    if (!error)
                    {
                        error = true;
                        error_str = "unknown error";
                    }
                }
#endif
                if (error)
                {
                    error_count++;
                    *m_ostream << error_str << std::endl;
                    print_run_error();
                }
                else if (!pass)
                {
                    fail_count++;
                    print_run_fail();
                }
                else
                {
                    pass_count++;
                    print_run_ok();
                }
                uint32_t testcase_time_ms = m_timestamp_ms_func() - testcase_start_timestamp_ms;
                print_run_end(suitename, testcase->name(), testcase_time_ms) << std::endl;
            }
            uint32_t testsuite_time_ms = m_timestamp_ms_func() - testsuite_start_timestamp_ms;

            print_separator() << testcases.size() << " tests from " << suitename << " (" << testsuite_time_ms << " ms)" << std::endl;
        }
        unsigned long int total_test = error_count + fail_count + pass_count;
        *m_ostream << "\n" << total_test << " tests executed in ";

        uint32_t total_exec_time_ms = m_timestamp_ms_func() - run_start_timestamp_ms;
        if (total_exec_time_ms < 1000)
        {
            *m_ostream << total_exec_time_ms << "ms";
        }
        else
        {
            uint32_t total_exec_time_sec = total_exec_time_ms / 1000;
            uint32_t total_exec_time_decimal_part = (total_exec_time_ms - (total_exec_time_sec * 1000)) / 100;

            *m_ostream << total_exec_time_sec << "." << total_exec_time_decimal_part << "s";
        }
        *m_ostream << ". (" << error_count << " errors, " << fail_count << " failures, " << pass_count << " successes)" << std::endl;

        if (error_count > 0 || fail_count > 0)
        {
            return 1;
        }

        m_success = true;
        return 0;
    }

    void TestRunner::set_ostream(std::ostream *const ostream)
    {
        m_ostream = ostream;
    }

    void TestRunner::set_timestamp_func(timestamp_ms_func_t func)
    {
        m_timestamp_ms_func = func;
    }

    std::ostream &TestRunner::print_fatal(std::string const &s)
    {
        return *m_ostream << "[FATAL ERROR] " << s << std::endl;
    }

    std::ostream &TestRunner::print_separator()
    {
        return *m_ostream << "[----------] ";
    }

    std::ostream &TestRunner::print_run_start(std::string const &suitename, std::string const &testcase_name)
    {
        return *m_ostream << "[ Run      ] " << suitename << "." << testcase_name;
    }

    std::ostream &TestRunner::print_run_ok()
    {
        return *m_ostream << "[       OK ] ";
    }

    std::ostream &TestRunner::print_run_error()
    {
        return *m_ostream << "[    Error ] ";
    }

    std::ostream &TestRunner::print_run_fail()
    {
        return *m_ostream << "[     Fail ] ";
    }

    std::ostream &TestRunner::print_run_end(std::string const &suitename, std::string const &testcase_name, unsigned long time_ms)
    {
        return *m_ostream << suitename << "." << testcase_name << " (" << time_ms << " ms)";
    }

    std::ostream &TestRunner::print_suite_start(std::string const &suitename, size_t const testcase_count)
    {
        print_separator() << testcase_count;
        if (testcase_count > 1)
        {
            *m_ostream << " tests";
        }
        else
        {
            *m_ostream << " test";
        }
        *m_ostream << " from " << suitename;
        return *m_ostream;
    }

    void TestRunner::register_test_case(std::string const &suite_name, TestCase *const testcase)
    {
        test_case_map_t::iterator iter = m_test_cases.find(suite_name);
        if (iter == m_test_cases.end())
        {
            m_test_cases[suite_name] = std::vector<TestCase *>();
        }

        m_test_cases[suite_name].push_back(testcase);
    }

} // namespace scrutinytest