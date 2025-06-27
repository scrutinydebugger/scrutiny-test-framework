//    config.hpp
//        Project wide configuration, can be set by cmake
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-test-framework)
//
//   Copyright (c) 2025 Scrutiny Debugger

#ifndef _SCRUTINYTEST_CONFIG_H_
#define _SCRUTINYTEST_CONFIG_H_

#ifndef SCRUTINYTEST_HAVE_EXCEPTIONS
#define SCRUTINYTEST_HAVE_EXCEPTIONS 0
#endif

#ifndef SCRUTINYTEST_NO_DETAILS
#define SCRUTINYTEST_NO_DETAILS 0
#endif

#ifndef SCRUTINYTEST_NO_OUTPUT
#define SCRUTINYTEST_NO_OUTPUT 0
#endif

#ifndef SCRUTINYTEST_MAX_TEST_CASES
#define SCRUTINYTEST_MAX_TEST_CASES 1024
#endif

#ifndef SCRUTINYTEST_MAX_TEST_SUITES
#define SCRUTINYTEST_MAX_TEST_SUITES 128
#endif

#endif