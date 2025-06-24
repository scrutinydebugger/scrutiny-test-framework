//    testresult.cpp
//        The class that gets injected in the test body to report the status of the test case
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-embedded)
//
//   Copyright (c) 2025 Scrutiny Debugger

#include "scrutinytest/testresult.hpp"

#include <ostream>
#include <sstream>

namespace scrutinytest
{
    TestResult::TestResult(std::ostream &stream) :
        m_failure_log_stream(),
        m_ostream(stream),
        m_failure_count(0)
    {
    }

    std::ostream &TestResult::record_failure()
    {
        m_failure_count++;
        return m_ostream;
    }

} // namespace scrutinytest