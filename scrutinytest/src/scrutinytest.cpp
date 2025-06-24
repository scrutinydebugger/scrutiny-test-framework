#include "scrutinytest/scrutinytest.hpp"
#include "scrutinytest/testcase_handler.hpp"

#include <ostream>
#include <string>

namespace scrutinytest
{
    void set_ostream(std::ostream *ostream)
    {
        MainRunner::get()->set_ostream(ostream);
    }

    void set_timestamp_func(timestamp_ms_func_t func)
    {
        MainRunner::get()->set_timestamp_func(func);
    }

    int main()
    {
        return MainRunner::get()->run();
    }
} // namespace scrutinytest