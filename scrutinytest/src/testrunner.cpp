#include "scrutinytest/testrunner.hpp"
#include "scrutinytest/testresult.hpp"
#include <iostream>

namespace scrutinytest
{

    TestRunner::TestRunner() :
        m_ostream(&std::cout),
        m_test_cases(),
        m_setup_error_str(),
        m_setup_error(false),
        m_success(false)
    {
    }

    void set_ostream(std::ostream *stream);

    int TestRunner::run()
    {
        if (m_setup_error)
        {
            print_fatal(m_setup_error_str);
            return -1;
        }

        for (test_case_map_t::iterator it = m_test_cases.begin(); it != m_test_cases.end(); it++)
        {
            std::string const &suitename = it->first;
            std::vector<TestCase *> &testcases = it->second;
            print_suite_start(suitename, testcases.size()) << std::endl;

            for (int i = 0; i < testcases.size(); i++)
            {
                TestCase *testcase = testcases[i];
                TestResult result(*m_ostream);

                bool error = false;
                bool pass = false;
                std::string error_str;
                try
                {
                    print_run_start(suitename, testcase->name()) << std::endl;
                    testcase->setUp();
                    try
                    {
                        testcase->body()(&result);
                        result.finalize();
                        if (result.failure_count() == 0)
                        {
                            pass = true;
                        }
                    }
                    catch (const std::exception &e)
                    {
                        error = true;
                        error_str = e.what();
                    }
                    testcase->tearDown();
                }
                catch (const std::exception &e)
                {
                    if (!error)
                    {
                        error = true;
                        error_str = e.what();
                    }
                }

                if (error)
                {
                    print_run_error() << error_str << std::endl;
                }
                else if (!pass)
                {
                    print_run_fail() << std::endl;
                }
                else
                {
                    print_run_ok(suitename, testcase->name(), 0) << std::endl;
                }
            }

            print_separator() << testcases.size() << "tests from " << suitename << std::endl;
        }

        if (!m_success)
        {
            return -2;
        }

        return 0;
    }

    void TestRunner::set_ostream(std::ostream *const ostream)
    {
        m_ostream = ostream;
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

    std::ostream &TestRunner::print_run_ok(std::string const &suitename, std::string const &testcase_name, unsigned long time_ms)
    {
        return *m_ostream << "[       OK ] " << suitename << "." << testcase_name << " (" << time_ms << " ms)";
    }

    std::ostream &TestRunner::print_run_error()
    {
        return *m_ostream << "[    Error ] ";
    }

    std::ostream &TestRunner::print_run_fail()
    {
        return *m_ostream << "[     Fail ] ";
    }

    std::ostream &TestRunner::print_suite_start(std::string const &suitename, size_t const testcase_count)
    {
        print_separator() << testcase_count;
        if (testcase_count > 1)
        {
            *m_ostream << "tests";
        }
        else
        {
            *m_ostream << "test";
        }
        *m_ostream << " from " << suitename;
        return *m_ostream;
    }

    void TestRunner::register_test_case(std::string const &suite_name, TestCase *const testcase)
    {
        test_case_map_t::iterator iter = m_test_cases.find(suite_name);
        if (iter == m_test_cases.end())
        {
            std::vector<TestCase *> vec;
            vec.reserve(1);
            m_test_cases[suite_name] = vec;
        }

        m_test_cases[suite_name].push_back(testcase);
    }

} // namespace scrutinytest