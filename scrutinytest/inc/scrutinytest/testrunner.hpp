//    testrunner.hpp
//        The class that will iterate all test suites and run the test cases
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-embedded)
//
//   Copyright (c) 2025 Scrutiny Debugger

#ifndef _SCRUTINY_TESTRUNNER_HPP_
#define _SCRUTINY_TESTRUNNER_HPP_

#include <map>
#include <ostream>
#include <string>
#include <vector>

#include "scrutinytest/testcase.hpp"
#include "scrutinytest/types.hpp"

namespace scrutinytest
{
    class TestCase;
    typedef std::map<std::string, std::vector<TestCase *> > test_case_map_t;

    class TestRunner
    {
      public:
        TestRunner();
        void set_ostream(std::ostream *const stream);
        void set_timestamp_func(timestamp_ms_func_t func);
        void register_test_case(std::string const &suite_name, TestCase *const testcase);
        int run();

      private:
        std::ostream &print_suite_start(std::string const &suitename, size_t const testcase_count);

        std::ostream &print_fatal(std::string const &s);
        std::ostream &print_separator();
        std::ostream &print_run_start(std::string const &suitename, std::string const &testcase_name);
        std::ostream &print_run_end(std::string const &suitename, std::string const &testcase_name, unsigned long time_ms);
        std::ostream &print_run_ok();
        std::ostream &print_run_error();
        std::ostream &print_run_fail();

        std::ostream *m_ostream;
        test_case_map_t m_test_cases;
        std::string m_setup_error_str;
        timestamp_ms_func_t m_timestamp_ms_func;

        bool m_setup_error;
        bool m_success;
    };

    class MainRunner
    {
      public:
        static TestRunner *get();
    };

} // namespace scrutinytest
#endif
