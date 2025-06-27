#ifndef _SCRUTINYTEST_STREAMS_HPP_
#define _SCRUTINYTEST_STREAMS_HPP_

#include "scrutinytest/macros.hpp"

#if SCRUTINYTEST_COMPACT
#define SCRUTINYTEST_HAS_STREAM 0
#else
#define SCRUTINYTEST_HAS_STREAM 1
#endif

#if SCRUTINYTEST_HAS_STREAM
#include <ostream>
#include <sstream>
#define ENDL std::endl
#else
#define ENDL ""
#endif

namespace scrutinytest
{
#if SCRUTINYTEST_HAS_STREAM
    class NullBuffer : public std::streambuf
    {
      public:
        int overflow(int c) { return c; }
    };
#endif

    class NullStream
    {
      public:
        inline char const *str() { return ""; }
    };

    template <typename T> NullStream &operator<<(NullStream &s, T const &arg)
    {
        static_cast<void>(arg);
        return s;
    }

#if SCRUTINYTEST_COMPACT
    typedef scrutinytest::NullStream ostream;
    typedef scrutinytest::NullStream ostringstream;
#else
    typedef std::ostream ostream;
    typedef std::ostringstream ostringstream;
#endif
} // namespace scrutinytest

#endif