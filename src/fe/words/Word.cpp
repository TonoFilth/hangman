#include "fe/words/Word.h"

using namespace std;

namespace fe
{

// =============================================================================
//	CONSTANTS
// =============================================================================
const string DEF_WORD_STRING("Default Word");
const string DEF_WORD_HINT("");
const TWordID ERR_WORD_ID(0);
const Word InvalidWord("743506C7-2C4A-4D46-9342-93CE76653880",
					   "1C72F9AA-CB95-4517-A599-98F6B4FEBECC");

// =============================================================================
//	NON-MEMBER FUNCTIONS
// =============================================================================
bool operator==(const Word& wordA, const Word& wordB)
{
	return (wordA.m_String == wordB.m_String && wordA.m_Hint == wordB.m_Hint);
}

bool operator!=(const Word& wordA, const Word& wordB)
{
	return (wordA.m_String != wordB.m_String || wordA.m_Hint != wordB.m_Hint);
}

// =============================================================================
//	STATIC FIELDS
// =============================================================================
TWordID Word::WORD_ID = 0;

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
Word::Word(const string& str, const string& hint) :
	m_ID(WORD_ID++),
	m_String(str),
	m_Hint(hint)
{
}

Word::Word(const Word& toCopy)
{
	Copy(toCopy);
}

Word& Word::operator=(const Word& toCopy)
{
	if (this == &toCopy)
		return *this;

	Copy(toCopy);
	return *this;
}

Word::~Word()
{
}

// =============================================================================
//	PRIVATE AND PROTECTED METHODS
// =============================================================================
void Word::Copy(const Word& toCopy)
{
	//m_ID	 = WORD_ID++;
	m_ID	 = toCopy.m_ID;
	m_String = toCopy.m_String;
	m_Hint 	 = toCopy.m_Hint;
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
TWordID Word::GetID() const
{
	return m_ID;
}

const string& Word::GetString() const
{
	return m_String;
}

const string& Word::GetHint() const
{
	return m_Hint;
}

void Word::SetString(const string& str)
{
	m_String = str;
}

void Word::SetHint(const string& hint)
{
	m_Hint = hint;
}

// =============================================================================
//	QUESTION METHODS
// =============================================================================
bool Word::IsValid() const
{
	return m_ID		!= ERR_WORD_ID			||
		   m_String != InvalidWord.m_String ||
		   m_Hint   != InvalidWord.m_Hint;
}

// =============================================================================
//	DEBUG METHODS
// =============================================================================
void Word::PrintDebug(const string& spaces) const
{
	cout << spaces << "WORD" << endl;
	cout << spaces << "  ID:     " << m_ID << endl;
	cout << spaces << "  String: \"" << m_String << "\"" << endl;
	cout << spaces << "  Hint:   \"" << m_Hint << "\"" << endl;
}

}
