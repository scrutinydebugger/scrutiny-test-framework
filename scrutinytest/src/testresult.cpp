#include "scrutinytest/testresult.hpp"

#include <ostream>
#include <sstream>

namespace scrutinytest
{

    class NullBuffer : public std::streambuf
    {
      public:
        int overflow(int c) { return c; }
    };

    NullBuffer null_buffer;
    std::ostream null_stream(&null_buffer);

    TestResult::TestResult(std::ostream &stream) :
        m_failure_log_stream(),
        m_ostream(stream),
        m_failure_count(0)
    {
    }

    std::ostream &TestResult::record_assertion(bool condition)
    {
        if (!condition)
        {
            flush_failures();
            m_failure_count++;
            return m_failure_log_stream;
        }
        return null_stream; // pass
    }

    void TestResult::finalize()
    {
        flush_failures();
    }

    void TestResult::flush_failures()
    {
        std::string content = m_failure_log_stream.str();
        if (content.size() > 0)
        {
            m_ostream << content << std::endl;
        }
        m_failure_log_stream.str("");
    }
} // namespace scrutinytest