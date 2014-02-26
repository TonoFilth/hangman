#include <iostream>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>

#include "WordTest.h"
#include "CategoryTest.h"

using namespace fe;
using namespace CppUnit;

CPPUNIT_TEST_SUITE_REGISTRATION(WordTest);
CPPUNIT_TEST_SUITE_REGISTRATION(CategoryTest);

int main(int argc, char** argv)
{
	TestResult testresult;
	TestResultCollector collectedresults;
    BriefTestProgressListener progress;

    testresult.addListener(&collectedresults);
    testresult.addListener(&progress);

    TestRunner testrunner;
    testrunner.addTest (TestFactoryRegistry::getRegistry().makeTest());
    testrunner.run(testresult);

    CompilerOutputter compileroutputter(&collectedresults, std::cerr);
    compileroutputter.write();

	// Output XML for Jenkins CPPunit plugin
	/*ofstream xmlFileOut("cppTestBasicMathResults.xml");
	XmlOutputter xmlOut(&collectedresults, xmlFileOut);
	xmlOut.write();*/

    return collectedresults.wasSuccessful() ? 0 : 1;
}
