# Copyright (c) 2021-2023 Scrutiny Debugger
# License : MIT - See LICENSE file.
# Project : Scrutiny Debugger (github.com/scrutinydebugger/scrutiny-embedded)

cmake_minimum_required(VERSION 3.14)

project(scrutinytest)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${PROJECT_NAME} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/testrunner.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/testcase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/testresult.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/scrutinytest.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/>
    $<INSTALL_INTERFACE:inc>
)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE )
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Werror )
endif()


# ----- INSTALL -----
install(
    TARGETS ${PROJECT_NAME} 
    ARCHIVE DESTINATION ${INSTALL_FOLDER} 
)
