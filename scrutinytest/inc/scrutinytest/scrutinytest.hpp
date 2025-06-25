//    scrutinytest.hpp
//        The main header to include for the scrutinytest framework
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-embedded)
//
//   Copyright (c) 2025 Scrutiny Debugger

#ifndef _SCRUTINYTEST_HPP_
#define _SCRUTINYTEST_HPP_

#include "scrutinytest/macros.hpp"
#include "scrutinytest/testcase.hpp"
#include "scrutinytest/testcase_handler.hpp"
#include "scrutinytest/testresult.hpp"
#include "scrutinytest/testrunner.hpp"
#include "scrutinytest/types.hpp"

#include <ostream>
#include <stdint.h>

namespace scrutinytest
{
    class AssertShenanigan
    {
      public:
        // Allow to return AND log a message with an assert by taking advantage of the priority of operation
        // with oeprator= and the fact that his operator can return void.
        // Hacky stuff.
        template <typename T> void operator=(T const &x) { static_cast<void>(x); }
    };

    class TestFailure
    {
      public:
        template <typename T> bool operator=(T const &x)
        {
            static_cast<void>(x);
            return false;
        }
    };

    int main();
    void set_ostream(std::ostream *ostream);
    void set_timestamp_func(timestamp_ms_func_t func);

} // namespace scrutinytest

#endif // _SCRUTINYTEST_HPP__
