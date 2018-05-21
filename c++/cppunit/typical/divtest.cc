#include "divtest.hh"
#include "api.hh"

void DivTest::testInt()
{
    CPPUNIT_ASSERT_EQUAL(2, api::div(5, 2));
}

void DivTest::testDouble()
{
    CPPUNIT_ASSERT_DOUBLES_EQUAL(2.5, api::div(5.0, 2.0), 0.0001);
}
