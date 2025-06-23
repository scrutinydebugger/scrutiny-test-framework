#ifndef _SCRUTINYTEST_TESTCASE_HPP_
#define _SCRUTINYTEST_TESTCASE_HPP_

#include "scrutinytest/testrunner.hpp"
#include <string>

namespace scrutinytest
{
    class TestCaseHandler;
    class TestResult;

    typedef void (*testbody_t)(TestResult *);

    class TestCase
    {
        friend class TestCaseHandler;
        friend class TestRunner;

      public:
        virtual void setUp();
        virtual void tearDown();

        inline std::string name() const { return m_name; }

      protected:
        inline testbody_t body() const { return m_body; };
        inline TestCase *set_name(std::string const &name)
        {
            m_name = name;
            return this;
        }
        inline TestCase *set_body(testbody_t body)
        {
            m_body = body;
            return this;
        }
        std::string m_name;
        testbody_t m_body;
    };

} // namespace scrutinytest
#endif
