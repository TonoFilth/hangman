#include "fe/words/Word.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTANTS
// =============================================================================
const Word InvalidWord("ERROR", "ERROR");

// =============================================================================
//	NON-MEMBER FUNCTIONS
// =============================================================================
bool operator==(const Word& wordA, const Word& wordB)
{
	return (wordA.m_Word == wordB.m_Word && wordA.m_Hint == wordB.m_Hint);
}

bool operator!=(const Word& wordA, const Word& wordB)
{
	return (wordA.m_Word != wordB.m_Word || wordA.m_Hint != wordB.m_Hint);
}

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
Word::Word() :
	m_Word(u8""),
	m_Hint(u8"")
{
}

Word::Word(const string& word, const string& hint) :
	m_Word(word),
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
	m_Word = toCopy.m_Word;
	m_Hint = toCopy.m_Hint;
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
const string& Word::GetWord() const
{
	return m_Word;
}

const string& Word::GetHint() const
{
	return m_Hint;
}

void Word::SetWord(const string& word)
{
	m_Word = word;
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
	return (m_Word == InvalidWord.m_Word && m_Hint == InvalidWord.m_Hint);
}

}
