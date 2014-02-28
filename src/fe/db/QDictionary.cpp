#include "fe/db/QDictionary.h"

using namespace std;

namespace fe
{

// =============================================================================
//	CONSTANTS
// =============================================================================
const TDictionaryID ERR_DICTIONARY_ID = 0;

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
QDictionary::QDictionary(const TDictionaryID id,
						 const string& name,
						 const string& lang,
						 const string& cset,
						 const string& font) :
	Dictionary(name, lang, cset, font),
	m_ID(id)
{
}

QDictionary::QDictionary(const QDictionary& toCopy) : Dictionary(toCopy)
{
	m_ID = toCopy.m_ID;
}

QDictionary& QDictionary::operator=(const QDictionary& toCopy)
{
	if (this == &toCopy)
		return *this;

	Dictionary::operator=(toCopy);
	m_ID = toCopy.m_ID;
	
	return *this;
}

QDictionary::~QDictionary()
{
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
TDictionaryID QDictionary::GetID() const { return m_ID; }

}
