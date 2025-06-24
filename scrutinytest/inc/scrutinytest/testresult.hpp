//    testresult.hpp
//        The class that gets injected in the test body to report the status of the test case
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-embedded)
//
//   Copyright (c) 2025 Scrutiny Debugger

#ifndef _SCRUTINYTEST_TESTRESULT_
#define _SCRUTINYTEST_TESTRESULT_

#include <ostream>
#include <sstream>

namespace scrutinytest
{
    class TestResult
    {
      public:
        TestResult(std::ostream &stream);
        std::ostream &record_failure();
        inline unsigned int failure_count() const { return m_failure_count; }

      private:
        std::stringstream m_failure_log_stream;
        std::ostream &m_ostream;
        unsigned int m_failure_count;
    };
} // namespace scrutinytest

#endif // _SCRUTINYTEST_TESTRESULT_