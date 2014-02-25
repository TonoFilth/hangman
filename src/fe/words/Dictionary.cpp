#include "fe/words/Dictionary.h"

using namespace std;

namespace fe
{

// =============================================================================
//	CONSTANTS
// =============================================================================
const string DEF_DICTIONARY_NAME("Default Dictionary Name");
const string DEF_DICTIONARY_LANG("en-EN");
const string DEF_DICTIONARY_CHARACTER_SET("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
const TDictionaryID ERR_DICTIONARY_ID(0);
const Dictionary InvalidDictionary(nullptr,
								   "365E36C4-714E-4920-BA72-B9F3421B40B6",
								   "A39098EC-B0E4-4951-960E-1414A4BDED94",
								   "BEEF6007-CDE7-43EE-ACEB-655E0F5BB24C");

// =============================================================================
//	STATIC FIELDS
// =============================================================================
TDictionaryID Dictionary::DICTIONARY_ID = 0;

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
Dictionary::Dictionary(const TFontPtr& font,
			   		   const string& name,
			   		   const string& lang,
			   		   const string& cset) :
	m_ID(DICTIONARY_ID++),
	m_Name(name),
	m_Lang(lang),
	m_CharacterSet(cset),
	m_Font(font)
{
}

Dictionary::~Dictionary()
{
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
void Dictionary::AddCategory(const Category& category)
{
	if (ContainsCategory(category))
		return;

	m_CategoryMap[category.GetID()] = category;
}

void Dictionary::AddCategories(const TCategoryVec& categories)
{
	for (auto& category : categories)
		AddCategory(category);
}

void Dictionary::RemoveCategory(const Category& category)
{
	m_CategoryMap.erase(category.GetID());
}

void Dictionary::RemoveCategories(const TCategoryVec& categories)
{
	for (auto& category : categories)
		RemoveCategory(category);
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
TDictionaryID Dictionary::GetID() 			const { return m_ID; 			}
string 		  Dictionary::GetName() 		const { return m_Name; 			}
string 		  Dictionary::GetLanguage() 	const { return m_Lang; 			}
string 		  Dictionary::GetCharacterSet() const { return m_CharacterSet;	}
TFontPtr 	  Dictionary::GetFont() 		const { return m_Font; 			}

void Dictionary::SetName(const string& name)	  	 { m_Name = name; 		  }
void Dictionary::SetLanguage(const string& lang)  	 { m_Lang = lang;  		  }
void Dictionary::SetCharacterSet(const string& cset) { m_CharacterSet = cset; }
void Dictionary::SetFont(const TFontPtr& font)		 { m_Font = font; 		  }

// =============================================================================
//	QUESTION METHODS
// =============================================================================
bool Dictionary::IsEmpty() const { return m_CategoryMap.empty(); }

bool Dictionary::IsValid() const
{
	return m_ID   != ERR_DICTIONARY_ID        ||
		   m_Name != InvalidDictionary.m_Name ||
		   m_Lang != InvalidDictionary.m_Lang ||
		   m_CharacterSet != InvalidDictionary.m_CharacterSet;
}

bool Dictionary::ContainsCategory(const Category& category) const
{
	return m_CategoryMap.count(category.GetID()) == 1;
}

bool Dictionary::ContainsWord(const Word& word) const
{
	for (auto& kv : m_CategoryMap)
		if (kv.second.ContainsWord(word))
			return true;

	return false;
}

// =============================================================================
//	DEBUG METHODS
// =============================================================================
void Dictionary::PrintDebug(const string& spaces) const
{
	cout << spaces << "DICTIONARY" << endl;
	cout << spaces << "  ID:            " << m_ID << endl;
	cout << spaces << "  Name:          \"" << m_Name << "\"" << endl;
	cout << spaces << "  Language:      \"" << m_Lang << "\"" << endl;
	cout << spaces << "  Character Set: \"" << m_CharacterSet << "\"" << endl;
	cout << spaces << "  Categories:" << endl;

	for (auto& kv : m_CategoryMap)
		kv.second.PrintDebug(spaces + "  ");
}

}
