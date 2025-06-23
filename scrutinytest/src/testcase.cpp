#include "scrutinytest/testcase_handler.hpp"

#include <string>

namespace scrutinytest
{
    void TestCase::setUp() {}
    void TestCase::tearDown() {}

    TestCaseHandler::TestCaseHandler(std::string const &suitename, std::string const &casename, testbody_t body) :
        m_testcase()
    {
        m_testcase.set_name(casename);
        m_testcase.set_body(body);
        TestCaseHandler::get_runner()->register_test_case(suitename, &m_testcase);
    }

} // namespace scrutinytest