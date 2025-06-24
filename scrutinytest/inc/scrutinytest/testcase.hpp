//    testcase.hpp
//        A base class for every test case
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-embedded)
//
//   Copyright (c) 2025 Scrutiny Debugger

#ifndef _SCRUTINYTEST_TESTCASE_HPP_
#define _SCRUTINYTEST_TESTCASE_HPP_

#include "scrutinytest/macros.hpp"
#include "scrutinytest/testrunner.hpp"
#include <stddef.h>
#include <string>

#define EXPECT_BUF_EQ(buf1, buf2, size)                                                                                                              \
    SCRUTINYTEST_EXPECT_WITH_DETAILS(COMPARE_BUF(SCRUTINYTEST_RESULT, buf1, buf2, size), "EXPECT_BUF_EQ(" #buf1 "," #buf2 "," #size ")")
#define ASSERT_BUF_EQ(buf1, buf2, size)                                                                                                              \
    SCRUTINYTEST_ASSERT_WITH_DETAILS(COMPARE_BUF(SCRUTINYTEST_RESULT, buf1, buf2, size), "ASSERT_BUF_EQ(" #buf1 "," #buf2 "," #size ")")

#define EXPECT_BUF_SET(buf, val, size)                                                                                                               \
    SCRUTINYTEST_EXPECT_WITH_DETAILS(CHECK_BUF_SET(SCRUTINYTEST_RESULT, buf, val, size), "EXPECT_BUF_SET(" #buf "," #val "," #size ")")
#define ASSERT_BUF_SET(buf, val, size)                                                                                                               \
    SCRUTINYTEST_ASSERT_WITH_DETAILS(CHECK_BUF_SET(SCRUTINYTEST_RESULT, buf, val, size), "ASSERT_BUF_SET(" #buf "," #val "," #size ")")

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
        bool COMPARE_BUF(SCRUTINYTEST_RESULT_ARG, unsigned char const *candidate, unsigned char const *expected, size_t const size);
        bool CHECK_BUF_SET(SCRUTINYTEST_RESULT_ARG, unsigned char const *buffer, unsigned char const val, size_t const size);
        std::string m_name;
    };

} // namespace scrutinytest
#endif
