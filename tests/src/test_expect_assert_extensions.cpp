//    test_expect_assert_extensions.cpp
//        Validate custom assetion fucntions in a test suite
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-test-framework)
//
//   Copyright (c) 2025 Scrutiny Debugger

#include "scrutinytest/scrutinytest.hpp"

#include <iostream>

class MyTestCase2 : public scrutinytest::TestCase
{
  public:
    void setUp() { std::cout << "Custom setup : Success" << std::endl; }
    void tearDown() { std::cout << "Custom tearDown : Success" << std::endl; }

    int internal_var1;
    int internal_var2;
    int internal_var3;
};

TEST_F(MyTestCase2, buf_eq)
{
    unsigned char buf1[] = { 1, 2, 3, 4, 5, 6 };
    unsigned char buf2[] = { 1, 2, 3, 4, 5, 7 };

    // EXPECT_BUF_EQ(buf1, buf1, 6);
    // EXPECT_BUF_EQ(buf1, buf2, 6);
    ASSERT_BUF_EQ(buf1, buf2, 6);
}

TEST_F(MyTestCase2, Cabuf_setse1)
{
    unsigned char buf1[] = {
        1, 1, 1, 1, 1,
    };

    // EXPECT_BUF_EQ(buf1, buf1, 6);
    // EXPECT_BUF_EQ(buf1, buf2, 6);
    ASSERT_BUF_SET(buf1, 1, 5);
    std::cout << "ok" << std::endl;
    ASSERT_BUF_SET(buf1, 2, 5);
    std::cout << "Not supposed to see me" << std::endl;
}
