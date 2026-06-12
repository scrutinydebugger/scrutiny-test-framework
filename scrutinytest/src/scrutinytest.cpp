//    scrutinytest.cpp
//        The definition of scrutinytest global functions
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-test-framework)
//
//   Copyright (c) 2025 Scrutiny Debugger

#include "scrutinytest/scrutinytest.hpp"
#include "scrutinytest/streams.hpp"
#include "scrutinytest/testcase_handler.hpp"

#if SCRUTINYTEST_MODE == SCRUTINYTEST_MODE_CALLBACK
void __attribute__((weak)) scrutinytest_failure_callback()
{
}
#endif

namespace scrutinytest
{
    void set_ostream(scrutinytest::ostream *ostream)
    {
        MainRunner::get()->set_ostream(ostream);
    }

    void set_timestamp_func(timestamp_ms_func_t func)
    {
        MainRunner::get()->set_timestamp_func(func);
    }

    int main()
    {
        return MainRunner::get()->run();
    }

    unsigned long int pass_count()
    {
        return MainRunner::get()->pass_count();
    }

    unsigned long int error_count()
    {
        return MainRunner::get()->error_count();
    }

    unsigned long int failure_count()
    {
        return MainRunner::get()->failure_count();
    }
} // namespace scrutinytest
