#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestResult.h>

#include "sumtest.hh"
#include "divtest.hh"

CPPUNIT_TEST_SUITE_REGISTRATION(SumTest);
CPPUNIT_TEST_SUITE_REGISTRATION(DivTest);

int main()
{
    CppUnit::TextTestRunner runner;
    CppUnit::BriefTestProgressListener listener;
    runner.eventManager().addListener(&listener);
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    return runner.run() ? 0 : 1;
}
