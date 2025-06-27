//    streams.hpp
//        A layer to mock ostreams in case we build without support for c++ stdlib
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-test-framework)
//
//   Copyright (c) 2025 Scrutiny Debugger

#ifndef _SCRUTINYTEST_STREAMS_HPP_
#define _SCRUTINYTEST_STREAMS_HPP_

#include "scrutinytest/config.hpp"
#include "scrutinytest/macros.hpp"

#if !SCRUTINYTEST_NO_OUTPUT
#include <ostream>
#include <sstream>
#define ENDL std::endl
#else
#define ENDL ""
#endif

namespace scrutinytest
{
#if !SCRUTINYTEST_NO_OUTPUT
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

#if SCRUTINYTEST_NO_OUTPUT
    typedef scrutinytest::NullStream ostream;
    typedef scrutinytest::NullStream ostringstream;
#else
    typedef std::ostream ostream;
    typedef std::ostringstream ostringstream;
#endif
} // namespace scrutinytest

#endif // _SCRUTINYTEST_STREAMS_HPP_
