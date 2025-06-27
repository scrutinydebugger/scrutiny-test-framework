//    types.hpp
//        Some proejct wide types
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-test-framework)
//
//   Copyright (c) 2025 Scrutiny Debugger

#ifndef _SCRUTINYTEST_TYPES_HPP_
#define _SCRUTINYTEST_TYPES_HPP_

#include <stdint.h>

namespace scrutinytest
{
    typedef uint32_t (*timestamp_ms_func_t)();
    static char const *const TAB = "  ";
} // namespace scrutinytest
#endif
