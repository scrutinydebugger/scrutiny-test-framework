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

    class TestCase
    {
        friend class TestRunner;

      public:
        inline std::string name() const { return m_name; }

        inline TestCase *_set_name(std::string const &name)
        {
            m_name = name;
            return this;
        }

      protected:
        bool TEST_BUF_EQ(unsigned char const *candidate, unsigned char const *expected, size_t const size);
        bool TEST_BUF_SET(unsigned char const *buffer, unsigned char const val, size_t const size);
        bool TEST_IS_NEAR(double const a, double const b, double const abs_err = 1e-12);
        std::string m_name;
        TestResult *SCRUTINYTEST_RESULT;

      private:
        virtual void setUp();
        virtual void tearDown();
        virtual void body() = 0;
        inline TestCase *_set_result(TestResult *const result)
        {
            SCRUTINYTEST_RESULT = result;
            return this;
        }
    };

} // namespace scrutinytest
#endif
