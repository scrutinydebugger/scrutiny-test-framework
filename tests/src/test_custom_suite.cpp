//    test_custom_suite.cpp
//        Tries the TEST_F() macro
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-embedded)
//
//   Copyright (c) 2025 Scrutiny Debugger

#include "scrutinytest/scrutinytest.hpp"

#if SCRUTINYTEST_HAVE_EXCEPTIONS
#include <exception>
#endif

#include <iostream>

class MyTestCase : public scrutinytest::TestCase
{
  public:
    void SetUp() { std::cout << "Custom setup : Success" << std::endl; }
    void TearDown() { std::cout << "Custom tearDown : Success" << std::endl; }

    int internal_var1;
    int internal_var2;
    int internal_var3;
};

TEST_F(MyTestCase, Case1)
{
    internal_var1 = 300;
    internal_var2 = 200;
    internal_var3 = 200;

    EXPECT_EQ(internal_var2, internal_var3);
    EXPECT_NE(internal_var1, internal_var2);
    EXPECT_LT(internal_var2, internal_var1);
    EXPECT_LE(internal_var2, internal_var1);
    EXPECT_GT(internal_var1, internal_var2);
    EXPECT_GE(internal_var1, internal_var2);

    EXPECT_TRUE(internal_var2 == internal_var3);
    EXPECT_FALSE(internal_var2 == internal_var1);

    ASSERT_EQ(internal_var2, internal_var3);
    ASSERT_NE(internal_var1, internal_var2);
    ASSERT_LT(internal_var2, internal_var1);
    ASSERT_LE(internal_var2, internal_var1);
    ASSERT_GT(internal_var1, internal_var2);
    ASSERT_GE(internal_var1, internal_var2);

    ASSERT_TRUE(internal_var2 == internal_var3);
    ASSERT_FALSE(internal_var2 == internal_var1);
}

TEST_F(MyTestCase, Case2ThatTakesTime)
{
    for (volatile int i = 0; i < 100000000; i++)
        ;
}
