//    testcase.hpp
//        A base class for every test case
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-embedded)
//
//   Copyright (c) 2025 Scrutiny Debugger

#ifndef _SCRUTINYTEST_TESTCASE_HPP_
#define _SCRUTINYTEST_TESTCASE_HPP_

#include "scrutinytest/testrunner.hpp"
#include <string>

namespace scrutinytest
{
    class TestResult;

    class TestCase
    {
        friend class TestRunner;

      public:
        virtual void setUp();
        virtual void tearDown();
        virtual void body(scrutinytest::TestResult *const result) = 0;

        inline std::string name() const { return m_name; }

        inline TestCase *_set_name(std::string const &name)
        {
            m_name = name;
            return this;
        }

      protected:
        std::string m_name;
    };

} // namespace scrutinytest
#endif
