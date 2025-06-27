#ifndef _SCRUTINYTEST_TESTUISTE_H_
#define _SCRUTINYTEST_TESTUISTE_H_

#include "scrutinytest/testcase.hpp"

namespace scrutinytest
{
    template <typename T> class TestSuiteSingleton
    {
      public:
        static T *get(char const *name)
        {
            static T instance(name);
            return &instance;
        }

      protected:
        TestSuiteSingleton(){};
    };

    class TestSuite
    {
      public:
        void add_testcase(TestCase *const testcase);

      protected:
        TestSuite(char const *suitename) :
            m_suitename(suitename),
            m_suite_list()
        {
        }
        char const *m_suitename;
        TestCaseLinkedList m_suite_list;
    };
} // namespace scrutinytest

#endif // _SCRUTINYTEST_TESTUISTE_STORE_H_