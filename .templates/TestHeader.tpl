#ifndef __GUARD
#define __GUARD

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;
using namespace fe;

class __CLASS : public TestFixture
{
	CPPUNIT_TEST_SUITE(__CLASS);

	CPPUNIT_TEST(TestConstructors);
	CPPUNIT_TEST(TestCopyConstructor);
	CPPUNIT_TEST(TestAssignmentOperator);
	CPPUNIT_TEST(TestDestructor);

	CPPUNIT_TEST(TestGettersSetters);

	CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void TestConstructors();
	void TestCopyConstructor();
	void TestAssignmentOperator();
	void TestDestructor();

	void TestGettersSetters();
};

#endif
