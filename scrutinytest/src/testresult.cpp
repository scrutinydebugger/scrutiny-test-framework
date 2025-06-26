//    testresult.cpp
//        The class that gets injected in the test body to report the status of the test case
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-test-framework)
//
//   Copyright (c) 2025 Scrutiny Debugger

#include "scrutinytest/testresult.hpp"
#include "scrutinytest/streams.hpp"
#include "scrutinytest/types.hpp"

#include <string>

namespace scrutinytest
{
    TestResult::TestResult(scrutinytest::ostream &stream) :
        m_ostream(stream),
        m_buffer_stream(),
        m_failure_count(0)
    {
    }

    scrutinytest::ostream &TestResult::record_failure()
    {
        m_failure_count++;
        return m_ostream;
    }

    scrutinytest::ostream &TestResult::record_success()
    {
        return m_ostream;
    }

    std::string TestResult::msg_buffer_str()
    {
        std::string str = m_buffer_stream.str();
        if (str.size() > 0)
        {
            str = scrutinytest::TAB + str;
        }
        return str;
    }
} // namespace scrutinytest
