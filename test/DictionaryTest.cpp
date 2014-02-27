#include "DictionaryTest.h"

using namespace std;

// =============================================================================
//	TEST STARTUP / TEARDOWN
// =============================================================================
void DictionaryTest::setUp()
{
	wX = Word("x");
	wY = Word("y");
	wZ = Word("z");

	m_OneWordCat.AddWord(wX);

	m_ThreeWordCat.AddWord(wX);
	m_ThreeWordCat.AddWord(wY);
	m_ThreeWordCat.AddWord(wZ);
}

void DictionaryTest::tearDown()
{
	m_EmptyCat.Clear();
	m_OneWordCat.Clear();
	m_ThreeWordCat.Clear();
}

// =============================================================================
//	TEST CASES
// =============================================================================

// --------------------- CONSTRUCTORS, CPTOR, DTOR, ASSOP ----------------------

void DictionaryTest::TestConstructors()
{
	Dictionary d1, d2("name2"), d3("name3", "lang3"), d4("name4", "lang4", "cset4"),
			   d5("name5", "lang5", "cset5", "font5");

	CPPUNIT_ASSERT(d1.GetName() 		== DEF_DICTIONARY_NAME &&
				   d1.GetLanguage() 	== DEF_DICTIONARY_LANG &&
				   d1.GetCharacterSet() == DEF_DICTIONARY_CHARACTER_SET &&
				   d1.GetFont() 		== DEF_DICTIONARY_FONT);

	CPPUNIT_ASSERT(d2.GetName() 		== "name2" &&
				   d2.GetLanguage() 	== DEF_DICTIONARY_LANG &&
				   d2.GetCharacterSet() == DEF_DICTIONARY_CHARACTER_SET &&
				   d2.GetFont() 		== DEF_DICTIONARY_FONT);

	CPPUNIT_ASSERT(d3.GetName() 		== "name3" &&
				   d3.GetLanguage() 	== "lang3" &&
				   d3.GetCharacterSet() == DEF_DICTIONARY_CHARACTER_SET &&
				   d3.GetFont() 		== DEF_DICTIONARY_FONT);

	CPPUNIT_ASSERT(d4.GetName() 		== "name4" &&
				   d4.GetLanguage() 	== "lang4" &&
				   d4.GetCharacterSet() == "cset4" &&
				   d4.GetFont() 		== DEF_DICTIONARY_FONT);

	CPPUNIT_ASSERT(d5.GetName() 		== "name5" &&
				   d5.GetLanguage() 	== "lang5" &&
				   d5.GetCharacterSet() == "cset5" &&
				   d5.GetFont() 		== "font5");
}

void DictionaryTest::TestDestructor()
{
	Dictionary* d = new Dictionary("name", "lang", "cset", "font");
	CPPUNIT_ASSERT(d->GetName() 		== "name" &&
				   d->GetLanguage() 	== "lang" &&
				   d->GetCharacterSet() == "cset" &&
				   d->GetFont() 		== "font");
	delete d;
	d = new Dictionary();
	CPPUNIT_ASSERT(d->GetName() 		== DEF_DICTIONARY_NAME &&
				   d->GetLanguage() 	== DEF_DICTIONARY_LANG &&
				   d->GetCharacterSet() == DEF_DICTIONARY_CHARACTER_SET &&
				   d->GetFont() 		== DEF_DICTIONARY_FONT);
	delete d;
}

// ----------------------------- GETTERS & SETTERS -----------------------------

void DictionaryTest::TestGettersSetters()
{
	Dictionary d;

	d.SetName("name");
	d.SetLanguage("lang");
	d.SetCharacterSet("cset");
	d.SetFont("font");

	CPPUNIT_ASSERT(d.GetName() 		   == "name" &&
				   d.GetLanguage() 	   == "lang" &&
				   d.GetCharacterSet() == "cset" &&
				   d.GetFont() 		   == "font");
}

// -------------------------------- OTHER TESTS --------------------------------

void DictionaryTest::TestAddRemoveWordCategory()
{
	Word wA("a"), wB("b"), wC("c");
	Category c1("mycat1"), c2("mycat2");
	Dictionary d;

	// Single word, single category
	CPPUNIT_ASSERT(!d.ContainsWord(wA));
	CPPUNIT_ASSERT(!d.AddWord(wA, c1));
	CPPUNIT_ASSERT(!d.ContainsWord(wA));

	CPPUNIT_ASSERT(d.AddCategory(c1));
	CPPUNIT_ASSERT(d.AddWord(wA, c1));
	CPPUNIT_ASSERT(d.ContainsWord(wA));

	CPPUNIT_ASSERT(!d.RemoveWord(wB));
	CPPUNIT_ASSERT(d.RemoveWord(wA));
	CPPUNIT_ASSERT(!d.ContainsWord(wA));

	CPPUNIT_ASSERT(d.GetWordCount() == 0);

	// Multiple words, single category
	d.Clear();
	CPPUNIT_ASSERT(d.AddCategory(c1));
	CPPUNIT_ASSERT(d.AddWord(wA, c1));
	CPPUNIT_ASSERT(d.AddWord(wB, c1));
	CPPUNIT_ASSERT(d.AddWord(wC, c1));
	CPPUNIT_ASSERT(d.ContainsWord(wA));
	CPPUNIT_ASSERT(d.ContainsWord(wB));
	CPPUNIT_ASSERT(d.ContainsWord(wC));

	CPPUNIT_ASSERT(d.RemoveWord(wB));
	CPPUNIT_ASSERT(!d.ContainsWord(wB));
	CPPUNIT_ASSERT(!d.RemoveWord(wB));
	CPPUNIT_ASSERT(d.RemoveWord(wA));
	CPPUNIT_ASSERT(d.RemoveWord(wC));
	CPPUNIT_ASSERT(d.GetWordCount() == 0);

	// Single word, multiple categories
	d.Clear();
	CPPUNIT_ASSERT(d.AddCategory(c1));
	CPPUNIT_ASSERT(d.AddCategory(c2));
	CPPUNIT_ASSERT(!d.AddCategory(c1));
	CPPUNIT_ASSERT(!d.AddCategory(c2));

	CPPUNIT_ASSERT(d.AddWord(wA, c1));
	CPPUNIT_ASSERT(d.ContainsWord(wA));
	CPPUNIT_ASSERT(d.AddWord(wA, c2));
	CPPUNIT_ASSERT(d.ContainsWord(wA));

	CPPUNIT_ASSERT(!d.RemoveWord(wB));
	CPPUNIT_ASSERT(d.RemoveWord(wA));
	CPPUNIT_ASSERT(!d.ContainsWord(wA));
	CPPUNIT_ASSERT(d.GetWordCount() == 0);

	// Multiple words, multiple categories
	d.Clear();
	CPPUNIT_ASSERT(d.AddCategory(c1));
	CPPUNIT_ASSERT(d.AddCategory(c2));

	CPPUNIT_ASSERT(d.AddWord(wA, c1));
	CPPUNIT_ASSERT(d.AddWord(wB, c1));
	CPPUNIT_ASSERT(d.AddWord(wA, c2));
	CPPUNIT_ASSERT(d.AddWord(wC, c2));

	CPPUNIT_ASSERT(d.ContainsWord(wA) &&
				   d.ContainsWord(wB) &&
				   d.ContainsWord(wC));
	
	CPPUNIT_ASSERT(d.RemoveWord(wA));
	CPPUNIT_ASSERT(!d.ContainsWord(wA));
	CPPUNIT_ASSERT(d.RemoveWord(wB));
	CPPUNIT_ASSERT(d.RemoveWord(wC));
	CPPUNIT_ASSERT(!d.RemoveWord(wC));
	CPPUNIT_ASSERT(d.GetWordCount() == 0);
}

void DictionaryTest::TestAddRemoveWordsCategories()
{
	Word wA("a"), wB("b"), wC("c");
	Category c1("mycat1"), c2("mycat2"), c3("mycat3");
	Dictionary d;

	TWordVec words;
	words.push_back(wA);
	words.push_back(wB);
	words.push_back(wC);

	TCategoryVec categories;
	categories.push_back(c1);
	categories.push_back(c2);

	CPPUNIT_ASSERT(!d.ContainsAllWords(words));
	CPPUNIT_ASSERT(!d.AddWords(words, c1));
	CPPUNIT_ASSERT(!d.ContainsAllWords(words));

	CPPUNIT_ASSERT(d.AddCategories(categories));
	CPPUNIT_ASSERT(d.AddWords(words, c1));
	CPPUNIT_ASSERT(d.ContainsAllWords(words));
	CPPUNIT_ASSERT(d.ContainsAllCategories(categories));
	CPPUNIT_ASSERT(d.GetCategoryCount() == categories.size());
	CPPUNIT_ASSERT(d.GetWordCount() == words.size());

	CPPUNIT_ASSERT(d.AddCategory(c3));
	CPPUNIT_ASSERT(d.ContainsAllCategories(categories));
	CPPUNIT_ASSERT(d.RemoveCategories(categories));
	CPPUNIT_ASSERT(!d.ContainsCategory(c1));
	CPPUNIT_ASSERT(!d.ContainsCategory(c2));
	CPPUNIT_ASSERT(d.ContainsCategory(c3));
}

void DictionaryTest::TestIsValidAndInvalidDictionary()
{
	Dictionary d;

	CPPUNIT_ASSERT(d.IsValid());
	CPPUNIT_ASSERT(!InvalidDictionary.IsValid());
}