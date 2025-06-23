
#ifndef _SCRUTINYTEST_HPP__
#define _SCRUTINYTEST_HPP__

#include "scrutinytest/testcase.hpp"
#include "scrutinytest/testcase_handler.hpp"
#include "scrutinytest/testresult.hpp"
#include "scrutinytest/testrunner.hpp"

#include <ostream>

namespace scrutinytest
{
    int main();
    void set_ostream(std::ostream *ostream);

} // namespace scrutinytest

#define TEST(suitename, casename)                                                                                                                    \
    static void s_scrutinytest_funcbody_##suitename##_##casename(scrutinytest::TestResult *);                                                        \
    scrutinytest::TestCaseHandler g_scrutinytest_##suitename##_##casename(#suitename, #casename, s_scrutinytest_funcbody_##suitename##_##casename);  \
    void s_scrutinytest_funcbody_##suitename##_##casename(scrutinytest::TestResult *_scrutinytest_result)

#define EXPECT_EQ(v1, v2) _scrutinytest_result->record_assertion((v1) == (v2))

#endif // _SCRUTINYTEST_HPP__