//    testcase.hpp
//        A base class for every test case
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-test-framework)
//
//   Copyright (c) 2025 Scrutiny Debugger

#ifndef _SCRUTINYTEST_TESTCASE_HPP_
#define _SCRUTINYTEST_TESTCASE_HPP_

#include "scrutinytest/macros.hpp"
#include "scrutinytest/testrunner.hpp"
#include <stddef.h>

#define EXPECT_BUF_EQ(buf1, buf2, size)                                                                                                              \
    SCRUTINYTEST_EXPECT_WITH_DETAILS(TEST_BUF_EQ(buf1, buf2, size), "EXPECT_BUF_EQ(" #buf1 "," #buf2 "," #size ")")
#define ASSERT_BUF_EQ(buf1, buf2, size)                                                                                                              \
    SCRUTINYTEST_ASSERT_WITH_DETAILS(TEST_BUF_EQ(buf1, buf2, size), "ASSERT_BUF_EQ(" #buf1 "," #buf2 "," #size ")")

#define EXPECT_BUF_SET(buf, val, size) SCRUTINYTEST_EXPECT_WITH_DETAILS(TEST_BUF_SET(buf, val, size), "EXPECT_BUF_SET(" #buf "," #val "," #size ")")
#define ASSERT_BUF_SET(buf, val, size) SCRUTINYTEST_ASSERT_WITH_DETAILS(TEST_BUF_SET(buf, val, size), "ASSERT_BUF_SET(" #buf "," #val "," #size ")")

#define EXPECT_NEAR(v1, v2, absdiff) SCRUTINYTEST_EXPECT_WITH_DETAILS(TEST_IS_NEAR(v1, v2, absdiff), "EXPECT_NEAR(" #v1 "," #v2 "," #absdiff ")")
#define ASSERT_NEAR(v1, v2, absdiff) SCRUTINYTEST_ASSERT_WITH_DETAILS(TEST_IS_NEAR(v1, v2, absdiff), "ASSERT_NEAR(" #v1 "," #v2 "," #absdiff ")")

namespace scrutinytest
{
    class TestResult;
    class TestSuite;

    class TestCase
    {
        friend class TestRunner;

      public:
        inline char const *name() const { return m_name; }

        inline TestCase *_set_name(char const *const &name)
        {
            m_name = name;
            return this;
        }

        inline void _set_suite(char const *const suite) { m_suite = suite; }
        inline char const *suite() const { return m_suite; }

      protected:
        bool TEST_BUF_EQ(unsigned char const *candidate, unsigned char const *expected, size_t const size);
        bool TEST_BUF_SET(unsigned char const *buffer, unsigned char const val, size_t const size);
        bool TEST_IS_NEAR(double const a, double const b, double const abs_err = 1e-12);
        char const *m_name;
        char const *m_suite;
        TestResult *SCRUTINYTEST_RESULT;

      private:
        virtual void SetUp();
        virtual void TearDown();
        virtual void body() = 0;
        inline TestCase *_set_result(TestResult *const result)
        {
            SCRUTINYTEST_RESULT = result;
            return this;
        }
    };

} // namespace scrutinytest
#endif
