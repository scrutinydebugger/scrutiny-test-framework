//    testcase.cpp
//        A base class for every test case
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-embedded)
//
//   Copyright (c) 2025 Scrutiny Debugger

#include "scrutinytest/scrutinytest.hpp"

#include <stddef.h>
#include <string>

namespace scrutinytest
{
    void TestCase::setUp() {}
    void TestCase::tearDown() {}

    bool TestCase::TEST_BUF_EQ(unsigned char const *candidate, unsigned char const *expected, size_t const size)
    {
        for (uint32_t i = 0; i < size; ++i)
        {
            if (expected[i] != candidate[i])
            {
                SCRUTINYTEST_FAIL << "candidate[" << i << "] (" << static_cast<uint32_t>(candidate[i]) << ") != expected[" << i << "] ("
                                  << static_cast<uint32_t>(expected[i]) << ")\n";
            }
        }

        SCRUTINYTEST_PASS;
    }

    bool TestCase::TEST_BUF_SET(unsigned char const *buffer, unsigned char const val, size_t const size)
    {
        for (uint32_t i = 0; i < size; ++i)
        {
            if (buffer[i] != val)
            {
                SCRUTINYTEST_FAIL << "buffer[" << i << "] (" << static_cast<uint32_t>(buffer[i]) << ") != expected[" << i << "] ("
                                  << static_cast<uint32_t>(val) << ")\n";
            }
        }
        SCRUTINYTEST_PASS;
    }

} // namespace scrutinytest