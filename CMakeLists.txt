cmake_minimum_required(VERSION 3.14)

option(SCRUTINYTEST_BUILD_TESTS "Build some demo test for testing the test framework" OFF)
option(SCRUTINYTEST_DISABLE_EXCEPTIONS "Forcefully disable the usage of exceptions" OFF)
option(SCRUTINYTEST_NO_DETAILS "Avoid printing debug details on a failure. Save some const emmory" OFF)
option(SCRUTINYTEST_NO_OUTPUT "Do not print at all. For JTAG debug only" OFF)
option(SCRUTINYTEST_MAX_TEST_CASES "Maximum number of test cases (static allocation)" 1024)


add_compile_definitions( 
    SCRUTINYTEST_NO_DETAILS=$<BOOL:${SCRUTINYTEST_NO_DETAILS}>
    SCRUTINYTEST_NO_OUTPUT=$<BOOL:${SCRUTINYTEST_NO_OUTPUT}>
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