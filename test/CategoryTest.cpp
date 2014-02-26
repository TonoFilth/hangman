#include "CategoryTest.h"

// =============================================================================
//	TEST STARTUP / TEARDOWN
// =============================================================================
void CategoryTest::setUp()
{
	Word w1, w2("x"), w3("y", "z");
	m_DefaultWords.push_back(w1);
	m_DefaultWords.push_back(w2);
	m_DefaultWords.push_back(w3);
}

void CategoryTest::tearDown()
{
	m_DefaultCategory = Category();
}

// =============================================================================
//	TEST CASES
// =============================================================================

// --------------------- CONSTRUCTORS, CPTOR, DTOR, ASSOP ----------------------

void CategoryTest::TestConstructors()
{
	Category c1, c2("a"), c3("");

	CPPUNIT_ASSERT(c1.GetName() == DEF_CATEGORY_NAME);
	CPPUNIT_ASSERT(c2.GetName() == "a");
	CPPUNIT_ASSERT(c3.GetName() == "");
}

void CategoryTest::TestCopyConstructor()
{
	Category c1, c2(c1);
	CPPUNIT_ASSERT(c1 == c2);

	m_DefaultCategory.AddWords(m_DefaultWords);
	Category c3(m_DefaultCategory);
	CPPUNIT_ASSERT(c3 == m_DefaultCategory);
	CPPUNIT_ASSERT(c3.GetWordCount() == m_DefaultCategory.GetWordCount());
}

void CategoryTest::TestAssignmentOperator()
{
	Category c1, c2("a"), c3;

	c1 = c3;
	CPPUNIT_ASSERT(c1 == c3);

	c1 = c2;
	CPPUNIT_ASSERT(c1.GetName() == "a");

	m_DefaultCategory.AddWords(m_DefaultWords);
	c3 = m_DefaultCategory;
	CPPUNIT_ASSERT(c3.GetWordCount() == m_DefaultWords.size());
}

void CategoryTest::TestIdentityOperators()
{
	Category c1, c2("a"), c3("a"), c4(InvalidCategory);

	CPPUNIT_ASSERT(c1 == c1 && c1 != c2 && c1 != c4);
	CPPUNIT_ASSERT(c2 == c3);
	CPPUNIT_ASSERT(c4 != c1 && c4 != c2 && c4 != c3 && c4 == c4);
}

void CategoryTest::TestDestructor()
{
	Category* c = new Category("mycategory");
	c->AddWords(m_DefaultWords);
	delete c;
	
	c = new Category();
	CPPUNIT_ASSERT(c->GetName() == DEF_CATEGORY_NAME);
	CPPUNIT_ASSERT(c->GetWordCount() == 0);
	delete c;
}

// ----------------------------- GETTERS & SETTERS -----------------------------

void CategoryTest::TestGettersSetters()
{
	Category c;
	CPPUNIT_ASSERT(c.GetName() == DEF_CATEGORY_NAME);

	c.SetName("mycategory");
	CPPUNIT_ASSERT(c.GetName() == "mycategory");
}

// -------------------------------- OTHER TESTS --------------------------------

void CategoryTest::TestAddWord()
{
	Word w1, w2("a"), w3("a", "b");

	CPPUNIT_ASSERT(m_DefaultCategory.AddWord(w1));
	CPPUNIT_ASSERT(m_DefaultCategory.AddWord(w2));
	CPPUNIT_ASSERT(m_DefaultCategory.AddWord(w3));
	CPPUNIT_ASSERT(!m_DefaultCategory.AddWord(InvalidWord));

	m_DefaultCategory.RemoveWord(w2);
	m_DefaultCategory.RemoveWord(w3);

	CPPUNIT_ASSERT(!m_DefaultCategory.AddWord(w1));
	CPPUNIT_ASSERT(m_DefaultCategory.AddWord(w2));
	CPPUNIT_ASSERT(m_DefaultCategory.AddWord(w3));
}

void CategoryTest::TestAddWords()
{
	TWordVec vec;
	vec.push_back(Word("a"));
	vec.push_back(Word("b"));
	vec.push_back(Word("c"));

	CPPUNIT_ASSERT(m_DefaultCategory.AddWords(vec));
	CPPUNIT_ASSERT(!m_DefaultCategory.AddWords(vec));
	CPPUNIT_ASSERT(m_DefaultCategory.AddWords(m_DefaultWords));

	m_DefaultCategory.RemoveWord(Word("a"));
	CPPUNIT_ASSERT(!m_DefaultCategory.AddWords(vec));
	
	m_DefaultCategory.RemoveWord(Word("a"));
	m_DefaultCategory.RemoveWord(Word("b"));
	m_DefaultCategory.RemoveWord(Word("c"));
	CPPUNIT_ASSERT(m_DefaultCategory.AddWords(vec));
}

void CategoryTest::TestRemoveWord()
{
	Word w1, w2("", "");
	
	CPPUNIT_ASSERT(!m_DefaultCategory.RemoveWord(w1));
	CPPUNIT_ASSERT(!m_DefaultCategory.RemoveWord(w2));
	CPPUNIT_ASSERT(!m_DefaultCategory.RemoveWord(InvalidWord));

	m_DefaultCategory.AddWord(w1);
	m_DefaultCategory.AddWord(w2);
	m_DefaultCategory.AddWord(InvalidWord);

	CPPUNIT_ASSERT(m_DefaultCategory.RemoveWord(w1));
	CPPUNIT_ASSERT(m_DefaultCategory.RemoveWord(w2));
	CPPUNIT_ASSERT(!m_DefaultCategory.RemoveWord(InvalidWord));
}

void CategoryTest::TestRemoveWords()
{
	TWordVec vec;
	vec.push_back(Word("a"));
	vec.push_back(Word("b"));
	vec.push_back(Word("c"));

	CPPUNIT_ASSERT(!m_DefaultCategory.RemoveWords(vec));

	m_DefaultCategory.AddWords(vec);
	CPPUNIT_ASSERT(m_DefaultCategory.RemoveWords(vec));
	CPPUNIT_ASSERT(!m_DefaultCategory.RemoveWords(m_DefaultWords));

	m_DefaultCategory.Clear();

	TWordVec vec2;
	vec2.push_back(Word("d"));
	vec2.push_back(Word("b"));
	vec2.push_back(Word("e"));

	m_DefaultCategory.AddWords(vec);
	m_DefaultCategory.AddWords(vec2);

	CPPUNIT_ASSERT(m_DefaultCategory.RemoveWords(vec));
	CPPUNIT_ASSERT(!m_DefaultCategory.RemoveWords(vec2));

	CPPUNIT_ASSERT(!m_DefaultCategory.RemoveWord(Word("b")));
}

void CategoryTest::TestClear()
{
	m_DefaultCategory.Clear();
	CPPUNIT_ASSERT(m_DefaultCategory.IsEmpty());

	m_DefaultCategory.AddWords(m_DefaultWords);
	CPPUNIT_ASSERT(!m_DefaultCategory.IsEmpty());

	m_DefaultCategory.Clear();
	CPPUNIT_ASSERT(m_DefaultCategory.IsEmpty());
}

void CategoryTest::TestGetWords()
{
	CPPUNIT_ASSERT(m_DefaultCategory.GetWords().empty());

	m_DefaultCategory.AddWord(Word("a"));
	CPPUNIT_ASSERT(m_DefaultCategory.GetWords().size() == 1);

	m_DefaultCategory.Clear();
	m_DefaultCategory.AddWords(m_DefaultWords);
	CPPUNIT_ASSERT(m_DefaultCategory.GetWords().size() == m_DefaultWords.size());
}

void CategoryTest::TestRandomWord()
{
	Word w1("cat"), w2("cow"), w3("dog");
	TWordVec returned;

	m_DefaultCategory.AddWord(w1);
	m_DefaultCategory.AddWord(w2);
	m_DefaultCategory.AddWord(w3);

	Word w = m_DefaultCategory.GetRandomWord();
	CPPUNIT_ASSERT(find(returned.begin(), returned.end(), w) == returned.end());

	returned.push_back(w);
	w = m_DefaultCategory.GetRandomWord();
	CPPUNIT_ASSERT(find(returned.begin(), returned.end(), w) == returned.end());

	returned.push_back(w);
	w = m_DefaultCategory.GetRandomWord();
	CPPUNIT_ASSERT(find(returned.begin(), returned.end(), w) == returned.end());

	returned.push_back(w);
	w = m_DefaultCategory.GetRandomWord();
	CPPUNIT_ASSERT(find(returned.begin(), returned.end(), w) != returned.end());
}

void CategoryTest::TestWordCount()
{
	CPPUNIT_ASSERT(m_DefaultCategory.GetWordCount() == 0);

	m_DefaultCategory.AddWord(Word("a"));
	CPPUNIT_ASSERT(m_DefaultCategory.GetWordCount() == 1);

	m_DefaultCategory.AddWords(m_DefaultWords);
	CPPUNIT_ASSERT(m_DefaultCategory.GetWordCount() == m_DefaultWords.size() + 1);

	m_DefaultCategory.RemoveWord(Word("a"));
	CPPUNIT_ASSERT(m_DefaultCategory.GetWordCount() == m_DefaultWords.size());

	m_DefaultCategory.Clear();
	CPPUNIT_ASSERT(m_DefaultCategory.GetWordCount() == 0);
}

void CategoryTest::TestIsEmpty()
{
	CPPUNIT_ASSERT(m_DefaultCategory.IsEmpty());

	m_DefaultCategory.AddWord(Word("a"));
	CPPUNIT_ASSERT(!m_DefaultCategory.IsEmpty());

	m_DefaultCategory.RemoveWord(Word("a"));
	CPPUNIT_ASSERT(m_DefaultCategory.IsEmpty());

	m_DefaultCategory.AddWords(m_DefaultWords);
	CPPUNIT_ASSERT(!m_DefaultCategory.IsEmpty());

	m_DefaultCategory.RemoveWords(m_DefaultWords);
	CPPUNIT_ASSERT(m_DefaultCategory.IsEmpty());

	m_DefaultCategory.AddWords(m_DefaultWords);
	CPPUNIT_ASSERT(!m_DefaultCategory.IsEmpty());

	m_DefaultCategory.Clear();
	CPPUNIT_ASSERT(m_DefaultCategory.IsEmpty());
}

void CategoryTest::TestIsValid()
{
	CPPUNIT_ASSERT(m_DefaultCategory.IsValid());
	
	Category c(InvalidCategory);
	CPPUNIT_ASSERT(!c.IsValid());
}

void CategoryTest::TestContainsWord()
{
	Word w1("a"), w2("a", "b");

	CPPUNIT_ASSERT(!m_DefaultCategory.ContainsWord(w1));
	CPPUNIT_ASSERT(!m_DefaultCategory.ContainsWord(w2));

	m_DefaultCategory.AddWord(w1);
	m_DefaultCategory.AddWord(w2);

	CPPUNIT_ASSERT(m_DefaultCategory.ContainsWord(w1));
	CPPUNIT_ASSERT(m_DefaultCategory.ContainsWord(w2));

	m_DefaultCategory.RemoveWord(w1);
	CPPUNIT_ASSERT(!m_DefaultCategory.ContainsWord(w1));
	CPPUNIT_ASSERT(m_DefaultCategory.ContainsWord(w2));

	m_DefaultCategory.RemoveWord(w2);
	CPPUNIT_ASSERT(!m_DefaultCategory.ContainsWord(w1));
	CPPUNIT_ASSERT(!m_DefaultCategory.ContainsWord(w2));

	m_DefaultCategory.AddWord(Word("myword"));
	CPPUNIT_ASSERT(m_DefaultCategory.ContainsWord(Word("myword")));
}

void CategoryTest::TestInvalidCategory()
{
	CPPUNIT_ASSERT(!InvalidCategory.IsValid());
	CPPUNIT_ASSERT(InvalidCategory.GetName() != DEF_CATEGORY_NAME);
}
