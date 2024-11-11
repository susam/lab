#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestResult.h>

class FooTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(FooTest);
    CPPUNIT_TEST(testFoo);
    CPPUNIT_TEST(testBar);
    CPPUNIT_TEST_SUITE_END();

protected:
    void testFoo();
    void testBar();
};

CPPUNIT_TEST_SUITE_REGISTRATION(FooTest);

void FooTest::testFoo()
{
    CPPUNIT_ASSERT_EQUAL(2, 1 + 1);
}

void FooTest::testBar()
{
    CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0, 1.0 + 2.0, 0.0001);
}

int main()
{
    CppUnit::TextTestRunner runner;
    CppUnit::BriefTestProgressListener listener;
    runner.eventManager().addListener(&listener);
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    return runner.run() ? 0 : 1;
}
