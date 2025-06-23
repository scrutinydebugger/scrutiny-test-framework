#ifndef _SCRUTINYTEST_TESTCASE_HANDLER_H_
#define _SCRUTINYTEST_TESTCASE_HANDLER_H_

#include <string>

#include "scrutinytest/testcase.hpp"
#include "scrutinytest/testrunner.hpp"

namespace scrutinytest
{
    class TestCaseHandler
    {
      public:
        TestCaseHandler(std::string const &suitename, std::string const &casename, testbody_t body);
        static TestRunner *get_runner();

      private:
        TestCase m_testcase;
    };
} // namespace scrutinytest

#endif // _SCRUTINYTEST_TESTCASE_HANDLER_H_