

#include "scrutinytest/testcase_handler.hpp"
#include "scrutinytest/testrunner.hpp"

namespace scrutinytest
{
    TestRunner *TestCaseHandler::get_runner()
    {
        static TestRunner s_runner;
        return &s_runner;
    }
} // namespace scrutinytest
