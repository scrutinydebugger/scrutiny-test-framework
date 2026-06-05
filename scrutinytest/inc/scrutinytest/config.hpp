//    config.hpp
//        Project wide configuration, can be set by cmake
//
//   - License : MIT - See LICENSE file.
//   - Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-test-framework)
//
//   Copyright (c) 2025 Scrutiny Debugger

#ifndef _SCRUTINYTEST_CONFIG_H_
#define _SCRUTINYTEST_CONFIG_H_

#define SCRUTINYTEST_MODE_CALLBACK 1
#define SCRUTINYTEST_MODE_NO_OUTPUT 2
#define SCRUTINYTEST_MODE_NO_DETAILS 3
#define SCRUTINYTEST_MODE_FULL 4

#ifndef SCRUTINYTEST_HAVE_EXCEPTIONS
#define SCRUTINYTEST_HAVE_EXCEPTIONS 0
#endif

#ifndef SCRUTINYTEST_MODE
#define SCRUTINYTEST_MODE SCRUTINYTEST_MODE_FULL
#endif

#ifndef SCRUTINYTEST_MAX_TEST_CASES
#define SCRUTINYTEST_MAX_TEST_CASES 1024
#endif

#endif // _SCRUTINYTEST_CONFIG_H_
