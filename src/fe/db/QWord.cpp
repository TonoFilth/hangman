#include "fe/db/QWord.h"

using namespace std;

namespace fe
{

// =============================================================================
//	CONSTANTS
// =============================================================================
const TWordID ERR_WORD_ID = 0;

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
QWord::QWord(const TWordID id, const string& str, const string& hint) :
	Word(str, hint),
	m_ID(id)
{
}

QWord::QWord(const QWord& toCopy) : Word(toCopy)
{
	m_ID = toCopy.m_ID;
}

QWord& QWord::operator=(const QWord& toCopy)
{
	if (this == &toCopy)
		return *this;

	Word::operator=(toCopy);
	m_ID = toCopy.m_ID;
	
	return *this;
}

QWord::~QWord()
{
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
TWordID QWord::GetID() const { return m_ID; }

}
