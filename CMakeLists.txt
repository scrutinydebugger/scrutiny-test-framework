cmake_minimum_required(VERSION 3.14)

option(BUILD_TESTS "Activate test suite" OFF)

add_subdirectory(scrutinytest)
if (BUILD_TESTS)
    add_subdirectory(tests)
endif()