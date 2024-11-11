#ifndef SUMTEST_HH
#define SUMTEST_HH

#include <cppunit/extensions/HelperMacros.h>

class SumTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(SumTest);
    CPPUNIT_TEST(testInt);
    CPPUNIT_TEST(testDouble);
    CPPUNIT_TEST_SUITE_END();

protected:
    void testInt();
    void testDouble();
};

#endif
