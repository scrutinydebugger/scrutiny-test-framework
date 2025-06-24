//    testcase.cpp
//        A base class for every test case
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-embedded)
//
//   Copyright (c) 2025 Scrutiny Debugger

#include "scrutinytest/testcase_handler.hpp"

#include <string>

namespace scrutinytest
{
    void TestCase::setUp() {}
    void TestCase::tearDown() {}

} // namespace scrutinytest