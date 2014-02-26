#include "WordTest.h"

// =============================================================================
//	TEST STARTUP / TEARDOWN
// =============================================================================
void WordTest::setUp()
{

}

void WordTest::tearDown()
{

}

// =============================================================================
//	TEST CASES
// =============================================================================

// --------------------- CONSTRUCTORS, CPTOR, DTOR, ASSOP ----------------------

void WordTest::TestConstructors()
{
	Word w1, w2("word"), w3("word", "hint");
	
	CPPUNIT_ASSERT(w1.GetString() == DEF_WORD_STRING &&
				   w1.GetHint()   == DEF_WORD_HINT);
	CPPUNIT_ASSERT(w2.GetString() == "word" &&
				   w2.GetHint()   == DEF_WORD_HINT);
	CPPUNIT_ASSERT(w3.GetString() == "word" && w3.GetHint() == "hint");
}

void WordTest::TestCopyConstructor()
{
	Word w1, w2("word"), w3("word", "hint");
	Word copy1(w1), copy2(w2), copy3(w3);
	
	CPPUNIT_ASSERT(copy1.GetString() == DEF_WORD_STRING &&
				   copy1.GetHint()   == DEF_WORD_HINT);
	CPPUNIT_ASSERT(copy2.GetString() == w2.GetString() &&
				   copy2.GetHint()   == DEF_WORD_HINT);
	CPPUNIT_ASSERT(copy3.GetString() == w3.GetString() &&
				   copy3.GetHint()   == w3.GetHint());
}

void WordTest::TestAssignmentOperator()
{
	Word w1, w2("word"), w3("word", "hint");
	Word copy1, copy2, copy3;

	copy1 = w1;
	copy2 = w2;
	copy3 = w3;

	CPPUNIT_ASSERT(copy1.GetString() == DEF_WORD_STRING &&
				   copy1.GetHint()   == DEF_WORD_HINT);
	CPPUNIT_ASSERT(copy2.GetString() == w2.GetString() &&
				   copy2.GetHint()   == DEF_WORD_HINT);
	CPPUNIT_ASSERT(copy3.GetString() == w3.GetString() &&
				   copy3.GetHint()   == w3.GetHint());
}

void WordTest::TestIdentityOperators()
{
	Word w1, w2, w3("a"), w4("a"), w5("a", "b"), w6("a", "b");

	CPPUNIT_ASSERT(w1 == w2);
	CPPUNIT_ASSERT(w3 == w4);
	CPPUNIT_ASSERT(w5 == w6);

	CPPUNIT_ASSERT(w1 != w3 && w1 != w5);
	CPPUNIT_ASSERT(w3 != w5);
}

void WordTest::TestDestructor()
{
	Word* w = new Word("a", "b");
	delete w;

	w = new Word();
	CPPUNIT_ASSERT(w->GetString() == DEF_WORD_STRING &&
				   w->GetHint()   == DEF_WORD_HINT);
	delete w;
}

// ----------------------------- GETTERS & SETTERS -----------------------------

void WordTest::TestGettersSetters()
{
	Word w1, w2("a"), w3("a", "b");

	w1.SetString("c");

	w2.SetString("d");
	w2.SetHint("e");

	w3.SetString("f");
	w3.SetHint("g");

	CPPUNIT_ASSERT(w1.GetString() == "c" &&
				   w1.GetHint()   == DEF_WORD_HINT);
	CPPUNIT_ASSERT(w2.GetString() == "d" &&
				   w2.GetHint()   == "e");
	CPPUNIT_ASSERT(w3.GetString() == "f" &&
				   w3.GetHint()   == "g");
}

void WordTest::TestIsValid()
{
	Word w1, w2("a"), w3("a", "b"), w4(InvalidWord);

	CPPUNIT_ASSERT(w1.IsValid());
	CPPUNIT_ASSERT(w2.IsValid());
	CPPUNIT_ASSERT(w3.IsValid());
	CPPUNIT_ASSERT(!w4.IsValid());
}

void WordTest::TestInvalidWord()
{
	CPPUNIT_ASSERT(InvalidWord.GetString() != DEF_WORD_STRING);
	CPPUNIT_ASSERT(!InvalidWord.IsValid());
}
