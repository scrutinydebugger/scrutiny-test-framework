//    testrunner.hpp
//        The class that will iterate all test suites and run the test cases
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-test-framework)
//
//   Copyright (c) 2025 Scrutiny Debugger

#ifndef _SCRUTINY_TESTRUNNER_HPP_
#define _SCRUTINY_TESTRUNNER_HPP_

#include "scrutinytest/streams.hpp"
#include "scrutinytest/testcase.hpp"
#include "scrutinytest/types.hpp"
#include "stddef.h"

#define MAX_TEST_CASES 256
#define MAX_TEST_SUITES 64

namespace scrutinytest
{
    class TestCase;

    struct TestCaseLinkedList
    {
        TestCase *testcase;
        TestCaseLinkedList *next;
    };

    class TestRunner
    {
      public:
        TestRunner();
        void set_ostream(scrutinytest::ostream *const stream);
        void set_timestamp_func(timestamp_ms_func_t func);
        unsigned long int register_test_case(TestCase *const testcase);
        int run();

      private:
        scrutinytest::ostream &print_suite_start(char const *suitename, size_t const testcase_count);

        scrutinytest::ostream &print_fatal(char const *const s);
        scrutinytest::ostream &print_separator();
        scrutinytest::ostream &print_run_start(char const *const suitename, char const *const testcase_name);
        scrutinytest::ostream &print_run_end(char const *const suitename, char const *const testcase_name, unsigned long time_ms);
        scrutinytest::ostream &print_run_ok();
        scrutinytest::ostream &print_run_error();
        scrutinytest::ostream &print_run_fail();

        scrutinytest::ostream *m_ostream;
        char const *m_init_error_str;
        timestamp_ms_func_t m_timestamp_ms_func;

        bool m_init_error;
        bool m_success;

        TestCaseLinkedList m_testcase_storage[MAX_TEST_CASES];
        TestCaseLinkedList *m_testsuite_storage[MAX_TEST_SUITES];
        unsigned long int m_testcase_storage_cursor;
        unsigned long int m_testsuite_storage_cursor;
    };

    class MainRunner
    {
      public:
        static TestRunner *get();
    };

} // namespace scrutinytest
#endif
