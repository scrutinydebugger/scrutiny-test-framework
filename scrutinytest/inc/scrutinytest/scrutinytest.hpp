//    scrutinytest.hpp
//        The main header to include for the scrutinytest framework
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-embedded)
//
//   Copyright (c) 2025 Scrutiny Debugger

#ifndef _SCRUTINYTEST_HPP_
#define _SCRUTINYTEST_HPP_

#include "scrutinytest/assertions.hpp"
#include "scrutinytest/testcase.hpp"
#include "scrutinytest/testcase_handler.hpp"
#include "scrutinytest/testresult.hpp"
#include "scrutinytest/testrunner.hpp"
#include "scrutinytest/types.hpp"

#include <ostream>
#include <stdint.h>

namespace scrutinytest
{
    static std::string const TAB = "  ";

    class AssertShenanigan
    {
      public:
        // Allow to return AND log a message with an assert by taking advantage of the priority of operation
        // with oeprator= and the fact that his operator can return void.
        // Hacky stuff.
        template <typename T> void operator=(T const &x) { static_cast<void>(x); }
    };

    int main();
    void set_ostream(std::ostream *ostream);
    void set_timestamp_func(timestamp_ms_func_t func);

} // namespace scrutinytest

#define TEST(suitename, casename)                                                                                                                    \
    class ClassScrutinyTest_##suitename_##casename : public scrutinytest::TestCase                                                                   \
    {                                                                                                                                                \
      public:                                                                                                                                        \
        virtual void body(scrutinytest::TestResult *const _scrutinytest_result);                                                                     \
    };                                                                                                                                               \
    scrutinytest::TestCaseHandler<ClassScrutinyTest_##suitename_##casename> g_scrutinytest_##suitename##_##casename(#suitename, #casename);          \
    void ClassScrutinyTest_##suitename_##casename::body(scrutinytest::TestResult *_scrutinytest_result)

#define TEST_F(suiteclass, casename)                                                                                                                 \
    class ClassScrutinyTest_##suiteclass##casename : public suiteclass                                                                               \
    {                                                                                                                                                \
      public:                                                                                                                                        \
        virtual void body(scrutinytest::TestResult *const _scrutinytest_result);                                                                     \
    };                                                                                                                                               \
    scrutinytest::TestCaseHandler<ClassScrutinyTest_##suiteclass##casename> g_scrutinytest_##suiteclass##_##casename(#suiteclass, #casename);        \
    void ClassScrutinyTest_##suiteclass##casename::body(scrutinytest::TestResult *_scrutinytest_result)

#define SCRUTINY_RELATIONAL_2ARGS_FAILURE(v1, v2, macro_name, op)                                                                                    \
    _scrutinytest_result->record_failure() << "\nFAILED: " << macro_name << "(" #v1 ", " #v2 ") : " << __FILE__ << ":" << __LINE__ << '\n'           \
                                           << scrutinytest::TAB << #v1 ": " << (v1) << "\n"                                                          \
                                           << scrutinytest::TAB << #v2 ": " << (v2) << '\n'

#define SCRUTINY_BOOL_FAILURE(v1, macro_name, op)                                                                                                    \
    _scrutinytest_result->record_failure() << "\nFAILED: " << macro_name << "(" #v1 ") : " << __FILE__ << ":" << __LINE__ << '\n'                    \
                                           << scrutinytest::TAB << #v1 ": " << (v1) << "\n"

#define SCRUTINY_RELATIONAL_EXPECT_2ARGS(v1, v2, macro_name, op)                                                                                     \
    if (!((v1)op(v2)))                                                                                                                               \
    SCRUTINY_RELATIONAL_2ARGS_FAILURE(v1, v2, macro_name, op)

#define SCRUTINY_RELATIONAL_ASSERT_2ARGS(v1, v2, macro_name, op)                                                                                     \
    if (!((v1)op(v2)))                                                                                                                               \
    return scrutinytest::AssertShenanigan() = SCRUTINY_RELATIONAL_2ARGS_FAILURE(v1, v2, macro_name, op)

#define SCRUTINY_BOOL_EXPECT(v1, macro_name, op)                                                                                                     \
    if (!(op(v1)))                                                                                                                                   \
    SCRUTINY_BOOL_FAILURE(v1, macro_name, op)

#define SCRUTINY_BOOL_ASSERT(v1, macro_name, op)                                                                                                     \
    if (!(op(v1)))                                                                                                                                   \
    return scrutinytest::AssertShenanigan() = SCRUTINY_BOOL_FAILURE(v1, macro_name, op)

#define EXPECT_EQ(v1, v2) SCRUTINY_RELATIONAL_EXPECT_2ARGS(v1, v2, "EXPECT_EQ", ==)
#define EXPECT_NE(v1, v2) SCRUTINY_RELATIONAL_EXPECT_2ARGS(v1, v2, "EXPECT_NE", !=)
#define EXPECT_LT(v1, v2) SCRUTINY_RELATIONAL_EXPECT_2ARGS(v1, v2, "EXPECT_LT", <)
#define EXPECT_LE(v1, v2) SCRUTINY_RELATIONAL_EXPECT_2ARGS(v1, v2, "EXPECT_LE", <=)
#define EXPECT_GT(v1, v2) SCRUTINY_RELATIONAL_EXPECT_2ARGS(v1, v2, "EXPECT_GT", >)
#define EXPECT_GE(v1, v2) SCRUTINY_RELATIONAL_EXPECT_2ARGS(v1, v2, "EXPECT_GE", >=)

#define EXPECT_TRUE(v1) SCRUTINY_BOOL_EXPECT(v1, "EXPECT_TRUE", )
#define EXPECT_FALSE(v1) SCRUTINY_BOOL_EXPECT(v1, "EXPECT_FALSE", !)

#define ASSERT_EQ(v1, v2) SCRUTINY_RELATIONAL_ASSERT_2ARGS(v1, v2, "ASSERT_EQ", ==)
#define ASSERT_NE(v1, v2) SCRUTINY_RELATIONAL_ASSERT_2ARGS(v1, v2, "ASSERT_NE", !=)
#define ASSERT_LT(v1, v2) SCRUTINY_RELATIONAL_ASSERT_2ARGS(v1, v2, "ASSERT_LT", <)
#define ASSERT_LE(v1, v2) SCRUTINY_RELATIONAL_ASSERT_2ARGS(v1, v2, "ASSERT_LE", <=)
#define ASSERT_GT(v1, v2) SCRUTINY_RELATIONAL_ASSERT_2ARGS(v1, v2, "ASSERT_GT", >)
#define ASSERT_GE(v1, v2) SCRUTINY_RELATIONAL_ASSERT_2ARGS(v1, v2, "ASSERT_GE", >=)

#define ASSERT_TRUE(v1) SCRUTINY_BOOL_ASSERT(v1, "ASSERT_TRUE", )
#define ASSERT_FALSE(v1) SCRUTINY_BOOL_ASSERT(v1, "ASSERT_FALSE", !)

#endif // _SCRUTINYTEST_HPP__