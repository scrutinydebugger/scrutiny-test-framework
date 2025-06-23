#include "scrutinytest/scrutinytest.hpp"
#include "scrutinytest/testcase_handler.hpp"

#include <ostream>
#include <string>

namespace scrutinytest
{
    void set_ostream(std::ostream *ostream)
    {
        TestCaseHandler::get_runner()->set_ostream(ostream);
    }

    int main()
    {
        return TestCaseHandler::get_runner()->run();
    }
} // namespace scrutinytest