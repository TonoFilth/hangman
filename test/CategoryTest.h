#ifndef __CATEGORY_TEST_H__
#define __CATEGORY_TEST_H__

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "fe/words/Category.h"

using namespace CppUnit;
using namespace fe;

class CategoryTest : public TestFixture
{
	CPPUNIT_TEST_SUITE(CategoryTest);

	CPPUNIT_TEST(TestConstructors);
	CPPUNIT_TEST(TestCopyConstructor);
	CPPUNIT_TEST(TestAssignmentOperator);
	CPPUNIT_TEST(TestIdentityOperators);
	CPPUNIT_TEST(TestDestructor);

	CPPUNIT_TEST(TestAddWord);
	CPPUNIT_TEST(TestAddWords);
	CPPUNIT_TEST(TestRemoveWord);
	CPPUNIT_TEST(TestRemoveWords);
	CPPUNIT_TEST(TestClear);

	CPPUNIT_TEST(TestGettersSetters);

	CPPUNIT_TEST(TestGetWords);
	CPPUNIT_TEST(TestRandomWord);
	CPPUNIT_TEST(TestWordCount);

	CPPUNIT_TEST(TestIsEmpty);
	CPPUNIT_TEST(TestIsValid);
	CPPUNIT_TEST(TestContainsWord);

	CPPUNIT_TEST(TestInvalidCategory);

	CPPUNIT_TEST_SUITE_END();

private:
	Category m_DefaultCategory;
	TWordVec m_DefaultWords;

public:
	virtual void setUp();
	virtual void tearDown();

	void TestConstructors();
	void TestCopyConstructor();
	void TestAssignmentOperator();
	void TestIdentityOperators();
	void TestDestructor();

	void TestAddWord();
	void TestAddWords();
	void TestRemoveWord();
	void TestRemoveWords();
	void TestClear();

	void TestGettersSetters();

	void TestGetWords();
	void TestRandomWord();
	void TestWordCount();

	void TestIsEmpty();
	void TestIsValid();
	void TestContainsWord();

	void TestInvalidCategory();
};

#endif
