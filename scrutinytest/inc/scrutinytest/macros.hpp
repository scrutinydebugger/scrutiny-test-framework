//    macros.hpp
//        Project wide macros
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-test-framework)
//
//   Copyright (c) 2025 Scrutiny Debugger

#ifndef _SCRUTINYTEST_MACROS_H_
#define _SCRUTINYTEST_MACROS_H_

#define SCRUTINYTEST_RESULT _m_scrutinytest_result

#define SCRUTINYTEST_PASS return true
#define SCRUTINYTEST_FAIL return scrutinytest::TestFailure() = SCRUTINYTEST_RESULT->msg_buffer() // This returns false always

#ifndef SCRUTINYTEST_COMPACT
#ifdef NDEBUG
#define SCRUTINYTEST_COMPACT 1
#else
#define SCRUTINYTEST_COMPACT 0
#endif
#endif

#if SCRUTINYTEST_COMPACT

#define SCRUTINYTEST_EXPECT_WITH_DETAILS(BOOL_PREDICATE, DETAILS)                                                                                    \
    if (!(BOOL_PREDICATE))                                                                                                                           \
    SCRUTINYTEST_RESULT->record_failure() << "FAILED\n" << SCRUTINYTEST_RESULT->msg_buffer_str()

#define SCRUTINYTEST_ASSERT_WITH_DETAILS(BOOL_PREDICATE, DETAILS)                                                                                    \
    if (!(BOOL_PREDICATE))                                                                                                                           \
    return scrutinytest::AssertShenanigan() = SCRUTINYTEST_RESULT->record_failure() << "FAILED\n" << SCRUTINYTEST_RESULT->msg_buffer_str()

#else

#define SCRUTINYTEST_EXPECT_WITH_DETAILS(BOOL_PREDICATE, DETAILS)                                                                                    \
    if (!(BOOL_PREDICATE))                                                                                                                           \
    SCRUTINYTEST_RESULT->record_failure() << "FAILED: " << DETAILS << " : " << __FILE__ << ":" << __LINE__ << '\n'                                   \
                                          << SCRUTINYTEST_RESULT->msg_buffer_str()

#define SCRUTINYTEST_ASSERT_WITH_DETAILS(BOOL_PREDICATE, DETAILS)                                                                                    \
    if (!(BOOL_PREDICATE))                                                                                                                           \
    return scrutinytest::AssertShenanigan() = SCRUTINYTEST_RESULT->record_failure()                                                                  \
                                              << "FAILED: " << DETAILS << " : " << __FILE__ << ":" << __LINE__ << '\n'                               \
                                              << SCRUTINYTEST_RESULT->msg_buffer_str()
#endif

#define SCRUTINYTEST_EXPECT(BOOL_PREDICATE) SCRUTINYTEST_EXPECT_WITH_DETAILS(BOOL_PREDICATE, "")
#define SCRUTINYTEST_ASSERT(BOOL_PREDICATE) SCRUTINYTEST_ASSERT_WITH_DETAILS(BOOL_PREDICATE, "")

#define TEST(suitename, casename)                                                                                                                    \
    class ClassScrutinyTest_##suitename_##casename : public scrutinytest::TestCase                                                                   \
    {                                                                                                                                                \
      public:                                                                                                                                        \
        virtual void body();                                                                                                                         \
    };                                                                                                                                               \
    scrutinytest::TestCaseHandler<ClassScrutinyTest_##suitename_##casename> g_scrutinytest_##suitename##_##casename(#suitename, #casename);          \
    void ClassScrutinyTest_##suitename_##casename::body()

#define TEST_F(suiteclass, casename)                                                                                                                 \
    class ClassScrutinyTest_##suiteclass##casename : public suiteclass                                                                               \
    {                                                                                                                                                \
      public:                                                                                                                                        \
        virtual void body();                                                                                                                         \
    };                                                                                                                                               \
    scrutinytest::TestCaseHandler<ClassScrutinyTest_##suiteclass##casename> g_scrutinytest_##suiteclass##_##casename(#suiteclass, #casename);        \
    void ClassScrutinyTest_##suiteclass##casename::body()

#define SCRUTINY_RELATIONAL_2ARGS_FAILURE_MSG(v1, v2) scrutinytest::TAB << #v1 ": " << (v1) << "\n" << scrutinytest::TAB << #v2 ": " << (v2) << '\n'

#define SCRUTINY_BOOL_FAILURE_MSG(v) scrutinytest::TAB << #v ": " << (v) << "\n"

#define SCRUTINY_RELATIONAL_EXPECT_2ARGS(v1, v2, macro_name, op)                                                                                     \
    SCRUTINYTEST_EXPECT_WITH_DETAILS((v1)op(v2), macro_name "(" #v1 "," #v2 ")") << SCRUTINY_RELATIONAL_2ARGS_FAILURE_MSG(v1, v2)

#define SCRUTINY_RELATIONAL_ASSERT_2ARGS(v1, v2, macro_name, op)                                                                                     \
    SCRUTINYTEST_ASSERT_WITH_DETAILS((v1)op(v2), macro_name "(" #v1 "," #v2 ")") << SCRUTINY_RELATIONAL_2ARGS_FAILURE_MSG(v1, v2)

#define SCRUTINY_BOOL_EXPECT(v, macro_name, op) SCRUTINYTEST_EXPECT_WITH_DETAILS(op(v), macro_name "(" #v ")") << SCRUTINY_BOOL_FAILURE_MSG(v)
#define SCRUTINY_BOOL_ASSERT(v, macro_name, op) SCRUTINYTEST_ASSERT_WITH_DETAILS(op(v), macro_name "(" #v ")") << SCRUTINY_BOOL_FAILURE_MSG(v)

#define EXPECT_EQ(v1, v2) SCRUTINY_RELATIONAL_EXPECT_2ARGS(v1, v2, "EXPECT_EQ", ==)
#define EXPECT_NE(v1, v2) SCRUTINY_RELATIONAL_EXPECT_2ARGS(v1, v2, "EXPECT_NE", !=)
#define EXPECT_LT(v1, v2) SCRUTINY_RELATIONAL_EXPECT_2ARGS(v1, v2, "EXPECT_LT", <)
#define EXPECT_LE(v1, v2) SCRUTINY_RELATIONAL_EXPECT_2ARGS(v1, v2, "EXPECT_LE", <=)
#define EXPECT_GT(v1, v2) SCRUTINY_RELATIONAL_EXPECT_2ARGS(v1, v2, "EXPECT_GT", >)
#define EXPECT_GE(v1, v2) SCRUTINY_RELATIONAL_EXPECT_2ARGS(v1, v2, "EXPECT_GE", >=)

#define EXPECT_TRUE(v1) SCRUTINY_BOOL_EXPECT(v1, "EXPECT_TRUE", !!) // Double negation for a positive without leaving the field blank
#define EXPECT_FALSE(v1) SCRUTINY_BOOL_EXPECT(v1, "EXPECT_FALSE", !)

#define ASSERT_EQ(v1, v2) SCRUTINY_RELATIONAL_ASSERT_2ARGS(v1, v2, "ASSERT_EQ", ==)
#define ASSERT_NE(v1, v2) SCRUTINY_RELATIONAL_ASSERT_2ARGS(v1, v2, "ASSERT_NE", !=)
#define ASSERT_LT(v1, v2) SCRUTINY_RELATIONAL_ASSERT_2ARGS(v1, v2, "ASSERT_LT", <)
#define ASSERT_LE(v1, v2) SCRUTINY_RELATIONAL_ASSERT_2ARGS(v1, v2, "ASSERT_LE", <=)
#define ASSERT_GT(v1, v2) SCRUTINY_RELATIONAL_ASSERT_2ARGS(v1, v2, "ASSERT_GT", >)
#define ASSERT_GE(v1, v2) SCRUTINY_RELATIONAL_ASSERT_2ARGS(v1, v2, "ASSERT_GE", >=)

#define ASSERT_TRUE(v1) SCRUTINY_BOOL_ASSERT(v1, "ASSERT_TRUE", !!) // Double negation for a positive without leaving the field blank
#define ASSERT_FALSE(v1) SCRUTINY_BOOL_ASSERT(v1, "ASSERT_FALSE", !)

#endif //_SCRUTINYTEST_MACROS_H_
