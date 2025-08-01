//    testcase_handler.hpp
//        A wrapper that initialize a testcase. Only goal is to leave the TestCase constructor
//        empty so the user can extend easily
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-test-framework)
//
//   Copyright (c) 2025 Scrutiny Debugger

#ifndef _SCRUTINYTEST_TESTCASE_HANDLER_H_
#define _SCRUTINYTEST_TESTCASE_HANDLER_H_

#include "scrutinytest/testcase.hpp"
#include "scrutinytest/testrunner.hpp"

namespace scrutinytest
{
    template <typename CaseClass> class TestCaseHandler
    {
      public:
        TestCaseHandler(char const *const suitename, char const *const casename) :
            m_testcase()
        {
            m_testcase._set_suite(suitename);
            m_testcase._set_name(casename);

            MainRunner::get()->register_test_case(&m_testcase);
        }

      private:
        CaseClass m_testcase;
    };
} // namespace scrutinytest

#endif // _SCRUTINYTEST_TESTCASE_HANDLER_H_
