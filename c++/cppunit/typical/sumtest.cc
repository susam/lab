#include "sumtest.hh"
#include "api.hh"

void SumTest::testInt()
{
    CPPUNIT_ASSERT_EQUAL(3, api::add(1, 2));
}

void SumTest::testDouble()
{
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0, api::add(1.0, 2.0), 0.001);
}
