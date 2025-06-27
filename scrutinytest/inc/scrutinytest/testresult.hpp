//    testresult.hpp
//        The class that gets injected in the test body to report the status of the test case
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-test-framework)
//
//   Copyright (c) 2025 Scrutiny Debugger

#ifndef _SCRUTINYTEST_TESTRESULT_
#define _SCRUTINYTEST_TESTRESULT_

#include "scrutinytest/streams.hpp"

#if !SCRUTINYTEST_NO_OUTPUT
#include <string>
#endif

namespace scrutinytest
{
    class TestResult
    {
      public:
        TestResult(scrutinytest::ostream &stream);
        scrutinytest::ostream &record_failure();
        scrutinytest::ostream &record_success();
        inline unsigned int failure_count() const { return m_failure_count; }
        inline scrutinytest::ostream &msg_buffer() { return m_buffer_stream; }
#if !SCRUTINYTEST_NO_OUTPUT
        std::string msg_buffer_str();
#endif

        scrutinytest::ostream &m_ostream;
        scrutinytest::ostringstream m_buffer_stream;
        unsigned int m_failure_count;
    };
} // namespace scrutinytest

#endif // _SCRUTINYTEST_TESTRESULT_
