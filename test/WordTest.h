#ifndef __WORD_TEST_H__
#define __WORD_TEST_H__

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "fe/words/Word.h"

using namespace CppUnit;
using namespace fe;

class WordTest : public TestFixture
{
	CPPUNIT_TEST_SUITE(WordTest);

	CPPUNIT_TEST(TestConstructors);
	CPPUNIT_TEST(TestCopyConstructor);
	CPPUNIT_TEST(TestAssignmentOperator);
	CPPUNIT_TEST(TestIdentityOperators);
	CPPUNIT_TEST(TestDestructor);

	CPPUNIT_TEST(TestGettersSetters);
	CPPUNIT_TEST(TestIsValid);
	CPPUNIT_TEST(TestInvalidWord);

	CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp();
	virtual void tearDown();

	void TestConstructors();
	void TestCopyConstructor();
	void TestAssignmentOperator();
	void TestIdentityOperators();
	void TestDestructor();

	void TestGettersSetters();
	void TestIsValid();
	void TestInvalidWord();
};

#endif
