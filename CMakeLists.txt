cmake_minimum_required(VERSION 3.14)

option(SCRUTINYTEST_BUILD_TESTS "Build some demo test for testing the test framework" OFF)
option(SCRUTINYTEST_DISABLE_EXCEPTIONS "Forcefully disable the usage of exceptions" OFF)
option(SCRUTINYTEST_MODE "" "FULL")
option(SCRUTINYTEST_MAX_TEST_CASES "Maximum number of test cases (static allocation)" 1024)

if (${SCRUTINYTEST_MODE} STREQUAL "FULL")
    add_compile_definitions( SCRUTINYTEST_MODE=SCRUTINYTEST_MODE_FULL)
elseif(${SCRUTINYTEST_MODE} STREQUAL "NO_OUTPUT")
    add_compile_definitions( SCRUTINYTEST_MODE=SCRUTINYTEST_MODE_NO_OUTPUT)
elseif(${SCRUTINYTEST_MODE} STREQUAL "NO_DETAILS")
    add_compile_definitions( SCRUTINYTEST_MODE=SCRUTINYTEST_MODE_NO_DETAILS)
elseif(${SCRUTINYTEST_MODE} STREQUAL "CALLBACK")
    add_compile_definitions( SCRUTINYTEST_MODE=SCRUTINYTEST_MODE_CALLBACK)
else()
message(SEND_ERROR "Invalid mode")
endif()

add_compile_definitions( 
    SCRUTINYTEST_MAX_TEST_CASES=${SCRUTINYTEST_MAX_TEST_CASES}
)

if (SCRUTINYTEST_DISABLE_EXCEPTIONS)
    add_compile_definitions(SCRUTINYTEST_HAVE_EXCEPTIONS=0)
else()
    include(CheckCXXSourceCompiles)
    check_cxx_source_compiles("
    int main() {
        try {
            throw 42;
        } catch (int) {
            return 0;
        }
        return 1;
    }" COMPILER_SUPPORTS_EXCEPTIONS)

    if (COMPILER_SUPPORTS_EXCEPTIONS)
        add_compile_definitions(SCRUTINYTEST_HAVE_EXCEPTIONS=1)
    else()
        add_compile_definitions(SCRUTINYTEST_HAVE_EXCEPTIONS=0)
    endif()
endif()

add_subdirectory(scrutinytest)
if (SCRUTINYTEST_BUILD_TESTS)
    add_subdirectory(tests)
endif()