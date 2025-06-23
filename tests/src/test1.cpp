#include "scrutinytest/scrutinytest.hpp"

#include <iostream>

TEST(aaa, bbb)
{
    std::cout << "ya" << std::endl;
    EXPECT_EQ(true, false) << "FAIL";
}