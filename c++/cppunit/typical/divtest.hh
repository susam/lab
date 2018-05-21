#ifndef DIVTEST_HH
#define DIVTEST_HH

#include <cppunit/extensions/HelperMacros.h>

class DivTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(DivTest);
    CPPUNIT_TEST(testInt);
    CPPUNIT_TEST(testDouble);
    CPPUNIT_TEST_SUITE_END();

protected:
    void testInt();
    void testDouble();
};

#endif
