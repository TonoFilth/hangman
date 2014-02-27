#ifndef __DICTIONARY_TEST_H__
#define __DICTIONARY_TEST_H__

#include <iostream>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "fe/words/Dictionary.h"

using namespace CppUnit;
using namespace fe;

class DictionaryTest : public TestFixture
{
	CPPUNIT_TEST_SUITE(DictionaryTest);

	CPPUNIT_TEST(TestConstructors);
	CPPUNIT_TEST(TestDestructor);

	CPPUNIT_TEST(TestAddRemoveWordCategory);
	CPPUNIT_TEST(TestAddRemoveWordsCategories);

	CPPUNIT_TEST(TestGettersSetters);

	CPPUNIT_TEST(TestIsValidAndInvalidDictionary);

	CPPUNIT_TEST_SUITE_END();

private:
	Word wX, wY, wZ;
	Category m_EmptyCat, m_OneWordCat, m_ThreeWordCat;

public:
	virtual void setUp();
	virtual void tearDown();

	void TestConstructors();
	void TestCopyConstructor();
	void TestAssignmentOperator();
	void TestDestructor();

	void TestAddRemoveWordCategory();
	void TestAddRemoveWordsCategories();

	void TestGettersSetters();

	void TestIsValidAndInvalidDictionary();
};

#endif
