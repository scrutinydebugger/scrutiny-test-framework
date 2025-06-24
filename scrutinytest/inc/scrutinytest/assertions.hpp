#ifndef _SCRUTINYTEST_ASSERTIONS_HPP_
#define _SCRUTINYTEST_ASSERTIONS_HPP_

#include <sstream>

namespace scrutinytest
{
    class AssertionResult
    {

      public:
        AssertionResult(bool const success) :
            m_sstream(),
            m_success(success)
        {
        }

        inline std::ostream &ostream() { return m_sstream; }
        inline bool is_success() { return m_success; }

      private:
        std::ostringstream m_sstream;
        bool m_success;
    };

    class AssertionSuccess : public AssertionResult
    {
        AssertionSuccess() :
            AssertionResult(true)
        {
        }
    };

    class AssertionFailure : public AssertionResult
    {
        AssertionFailure() :
            AssertionResult(true)
        {
        }
    };

    template <typename T> AssertionResult &operator<<(AssertionResult &assertion_result, T const &v)
    {
        assertion_result.ostream() << v;
        return assertion_result;
    }
} // namespace scrutinytest

#endif