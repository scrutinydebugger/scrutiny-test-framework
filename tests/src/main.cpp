//    main.cpp
//        A main that can run some demo tests on an OS
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-test-framework)
//
//   Copyright (c) 2025 Scrutiny Debugger

#include "scrutinytest/scrutinytest.hpp"

#include <iostream>
#include <stdint.h>

#if __unix__
#include <time.h>
#define HAS_TIMESTAMP_FUNC
static uint32_t timestamp_ms_func()
{
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0)
    {
        return 0;
    }

    return static_cast<uint32_t>(ts.tv_sec * 1000) + static_cast<uint32_t>(ts.tv_nsec / 1000000);
}
#endif

int main(int argc, char *argv[])
{
#if !SCRUTINYTEST_NO_OUTPUT
    scrutinytest::set_ostream(&std::cout);
#endif
#ifdef HAS_TIMESTAMP_FUNC
    scrutinytest::set_timestamp_func(timestamp_ms_func);
#endif
    int main_result = scrutinytest::main();

    std::cout << "\n---- Stats ----" << '\n';
    std::cout << "Main output: " << main_result << '\n';
    std::cout << "Pass: " << scrutinytest::pass_count() << '\n';
    std::cout << "Failures: " << scrutinytest::failure_count() << '\n';
    std::cout << "Error: " << scrutinytest::error_count() << '\n';

    return main_result;
}
