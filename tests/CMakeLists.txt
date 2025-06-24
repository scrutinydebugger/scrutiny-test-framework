

cmake_minimum_required(VERSION 3.14)

project(scrutinytest_test)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/test_basic.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/test_custom_suite.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE scrutinytest)