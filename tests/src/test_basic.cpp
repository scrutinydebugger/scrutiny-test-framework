//    test_basic.cpp
//        Tries the TEST() macro
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-test-framework)
//
//   Copyright (c) 2025 Scrutiny Debugger

#include "scrutinytest/scrutinytest.hpp"

#if SCRUTINYTEST_HAVE_EXCEPTIONS
#include <exception>
#endif

#include <iostream>

TEST(Testsuite1, Case1)
{
    int my_var1 = 300;
    int my_var2 = 200;
    int my_var3 = 200;
    EXPECT_EQ(my_var2, my_var3);
    EXPECT_NE(my_var1, my_var2);
    EXPECT_LT(my_var2, my_var1);
    EXPECT_LE(my_var2, my_var1);
    EXPECT_GT(my_var1, my_var2);
    EXPECT_GE(my_var1, my_var2);

    EXPECT_TRUE(my_var2 == my_var3);
    EXPECT_FALSE(my_var2 == my_var1);

    ASSERT_EQ(my_var2, my_var3);
    ASSERT_NE(my_var1, my_var2);
    ASSERT_LT(my_var2, my_var1);
    ASSERT_LE(my_var2, my_var1);
    ASSERT_GT(my_var1, my_var2);
    ASSERT_GE(my_var1, my_var2);

    ASSERT_TRUE(my_var2 == my_var3);
    ASSERT_FALSE(my_var2 == my_var1);

    float a = 1.233;
    float b = 1.234;

    EXPECT_NEAR(a, b, 0.1);
}

#if SCRUTINYTEST_HAVE_EXCEPTIONS
#include <exception>
TEST(Testsuite1, CaseThatThrows)
{
    throw std::runtime_error("I crashed!");
}
#endif

TEST(Testsuite1, CaseThatFailsAnAssert)
{
    ASSERT_FALSE(true);
}
