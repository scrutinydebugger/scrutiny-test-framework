#ifndef _SCRUTINY_TESTRUNNER_HPP_
#define _SCRUTINY_TESTRUNNER_HPP_

#include <map>
#include <ostream>
#include <string>
#include <vector>

#include "scrutinytest/testcase.hpp"

namespace scrutinytest
{
    class TestCase;
    typedef std::map<std::string, std::vector<TestCase *> > test_case_map_t;

    class TestRunner
    {
      public:
        TestRunner();
        void set_ostream(std::ostream *const stream);
        void register_test_case(std::string const &suite_name, TestCase *const testcase);
        int run();

      private:
        std::ostream &print_suite_start(std::string const &suitename, size_t const testcase_count);

        std::ostream &print_fatal(std::string const &s);
        std::ostream &print_separator();
        std::ostream &print_run_start(std::string const &suitename, std::string const &testcase_name);
        std::ostream &print_run_ok(std::string const &suitename, std::string const &testcase_name, unsigned long time_ms);
        std::ostream &print_run_error();
        std::ostream &print_run_fail();

        std::ostream *m_ostream;
        test_case_map_t m_test_cases;
        std::string m_setup_error_str;

        bool m_setup_error;
        bool m_success;
    };

} // namespace scrutinytest
#endif
