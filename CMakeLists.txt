cmake_minimum_required(VERSION 3.14)

option(BUILD_TESTS "Activate test suite" OFF)
option(DISABLE_EXCEPTIONS "Forcefully disable the suage of exceptions" OFF)

if (DISABLE_EXCEPTIONS)
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
if (BUILD_TESTS)
    add_subdirectory(tests)
endif()