#include "fe/words/Word.h"

using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTANTS
// =============================================================================
const Word InvalidWord("ERROR", "ERROR");

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
Word::Word() :
	m_Word(""),
	m_Hint("")
{
}

Word::Word(const String& word, const String& hint) :
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
const String& Word::GetWord() const
{
	return m_Word;
}

const String& Word::GetHint() const
{
	return m_Hint;
}

void Word::SetWord(const String& word)
{
	m_Word = word;
}

void Word::SetHint(const String& hint)
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
