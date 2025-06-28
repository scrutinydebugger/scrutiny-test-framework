//    scrutinytest.hpp
//        The main header to include for the scrutinytest framework
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-test-framework)
//
//   Copyright (c) 2025 Scrutiny Debugger

#ifndef _SCRUTINYTEST_HPP_
#define _SCRUTINYTEST_HPP_

#include "scrutinytest/macros.hpp"
#include "scrutinytest/streams.hpp"
#include "scrutinytest/testcase.hpp"
#include "scrutinytest/testcase_handler.hpp"
#include "scrutinytest/testresult.hpp"
#include "scrutinytest/testrunner.hpp"
#include "scrutinytest/types.hpp"

#include <stdint.h>

namespace scrutinytest
{

    class AssertShenanigan
    {
      public:
        // Allow to return AND log a message with an assert by taking advantage of the priority of operation
        // with oeprator= and the fact that his operator can return void.
        // Hacky stuff.
        void operator=(scrutinytest::ostream &ostream) { ostream << '\n'; }
    };

    class TestFailure
    {
      public:
        // Allow to return AND log a message with an assert by taking advantage of the priority of operation
        // with oeprator= and the fact that his operator can return void.
        // Hacky stuff.
        bool operator=(scrutinytest::ostream &ostream)
        {
            ostream << '\n';
            return false;
        }
    };

    int main();
    void set_ostream(scrutinytest::ostream *ostream);
    void set_timestamp_func(timestamp_ms_func_t func);

} // namespace scrutinytest

#endif // _SCRUTINYTEST_HPP__
