//    testrunner.cpp
//        The class that will iterate all test suites and run the test cases
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-test-framework)
//
//   Copyright (c) 2025 Scrutiny Debugger

#include "scrutinytest/testrunner.hpp"
#include "scrutinytest/streams.hpp"
#include "scrutinytest/testresult.hpp"

#if SCRUTINYTEST_HAVE_EXCEPTIONS
#include <exception>
#endif

#include <stdlib.h>

namespace scrutinytest
{

#if SCRUTINYTEST_HAS_STREAM
    static scrutinytest::NullBuffer s_nullbuffer;
    static scrutinytest::ostream s_nullstream(&s_nullbuffer);
#else
    static scrutinytest::ostream s_nullstream;
#endif

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
        m_ostream(&s_nullstream),
        m_init_error_str(NULL),
        m_timestamp_ms_func(default_timestamp_ms_func),
        m_init_error(false),
        m_success(false),
        m_testcase_storage(),
        m_testsuite_storage(),
        m_testcase_storage_cursor(0),
        m_testsuite_storage_cursor(0)

    {
        for (unsigned int i = 0; i < MAX_TEST_CASES; i++)
        {
            m_testcase_storage[i].next = NULL;
            m_testcase_storage[i].testcase = NULL;
        }
        for (unsigned int i = 0; i < MAX_TEST_SUITES; i++)
        {
            m_testsuite_storage[i] = NULL;
        }
    }

    void set_ostream(scrutinytest::ostream *stream);

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
        for (unsigned long int suite_it = 0; suite_it < m_testsuite_storage_cursor; suite_it++)
        {
            if (m_testsuite_storage[suite_it] == NULL)
            {
                continue;
            }
            TestCaseLinkedList *node = m_testsuite_storage[suite_it];

            TestCase *testcase = m_testsuite_storage[suite_it]->testcase;
            if (testcase == NULL)
            {
                continue;
            }

            unsigned int nb_case = 1;
            TestCaseLinkedList *temp = node;
            while ((temp = temp->next) != NULL)
            {
                nb_case++;
            }

            char const *suitename = testcase->suite();

            *m_ostream << '\n';
            uint32_t testsuite_start_timestamp_ms = m_timestamp_ms_func();
            print_suite_start(suitename, nb_case) << ENDL;

            do
            {
                uint32_t testcase_start_timestamp_ms = m_timestamp_ms_func();
                TestCase *testcase = node->testcase;
                TestResult result(*m_ostream);
                testcase->_set_result(&result);

                bool error = false;
                bool pass = false;
                char const *error_str = NULL;
#if SCRUTINYTEST_HAVE_EXCEPTIONS
                try
                {
#endif
                    print_run_start(suitename, testcase->name()) << ENDL;
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
                    *m_ostream << error_str << ENDL;
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
                print_run_end(suitename, testcase->name(), testcase_time_ms) << ENDL;
            } while ((node = node->next) != NULL);
            uint32_t testsuite_time_ms = m_timestamp_ms_func() - testsuite_start_timestamp_ms;

            print_separator() << nb_case << " tests from " << suitename << " (" << testsuite_time_ms << " ms)" << ENDL;
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
        *m_ostream << ". (" << error_count << " errors, " << fail_count << " failures, " << pass_count << " successes)" << ENDL;

        if (error_count > 0 || fail_count > 0)
        {
            return 1;
        }

        m_success = true;
        return 0;
    }

    void TestRunner::set_ostream(scrutinytest::ostream *const ostream)
    {
        m_ostream = ostream;
    }

    void TestRunner::set_timestamp_func(timestamp_ms_func_t func)
    {
        m_timestamp_ms_func = func;
    }

    scrutinytest::ostream &TestRunner::print_fatal(char const *const s)
    {
        return *m_ostream << "[FATAL ERROR] " << s << ENDL;
    }

    scrutinytest::ostream &TestRunner::print_separator()
    {
        return *m_ostream << "[----------] ";
    }

    scrutinytest::ostream &TestRunner::print_run_start(char const *const suitename, char const *const testcase_name)
    {
        return *m_ostream << "[ Run      ] " << suitename << "." << testcase_name;
    }

    scrutinytest::ostream &TestRunner::print_run_ok()
    {
        return *m_ostream << "[       OK ] ";
    }

    scrutinytest::ostream &TestRunner::print_run_error()
    {
        return *m_ostream << "[    Error ] ";
    }

    scrutinytest::ostream &TestRunner::print_run_fail()
    {
        return *m_ostream << "[     Fail ] ";
    }

    scrutinytest::ostream &TestRunner::print_run_end(char const *const suitename, char const *const testcase_name, unsigned long time_ms)
    {
        return *m_ostream << suitename << "." << testcase_name << " (" << time_ms << " ms)";
    }

    scrutinytest::ostream &TestRunner::print_suite_start(char const *const suitename, size_t const testcase_count)
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

    unsigned long int TestRunner::register_test_case(TestCase *const testcase)
    {
        if (m_testcase_storage_cursor >= MAX_TEST_CASES)
        {
            m_init_error = true;
            m_init_error_str = "Too much tests";
            return 0;
        }
        unsigned long int const pos = m_testcase_storage_cursor++;

        TestCaseLinkedList *prev = NULL;
        for (unsigned int i = 0; i < pos; i++)
        {
            TestCaseLinkedList *const node = &m_testcase_storage[i];
            if (node->testcase->suite() == testcase->suite())
            {
                prev = node;
            }
        }

        m_testcase_storage[pos].testcase = testcase;
        if (prev != NULL)
        {
            prev->next = &m_testcase_storage[pos];
        }
        else
        {
            m_testsuite_storage[m_testsuite_storage_cursor++] = &m_testcase_storage[pos];
        }
        return pos;
    }

} // namespace scrutinytest
