#include "fe/words/Dictionary.h"

using namespace std;

namespace fe
{

// =============================================================================
//	CONSTANTS
// =============================================================================
const string 	 DEF_DICTIONARY_NAME("Default Dictionary Name");
const string 	 DEF_DICTIONARY_LANG("en-EN");
const string 	 DEF_DICTIONARY_CHARACTER_SET("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
const string	 DEF_DICTIONARY_FONT("Default Font TTF");
const Dictionary InvalidDictionary("365E36C4-714E-4920-BA72-B9F3421B40B6",
								   "A39098EC-B0E4-4951-960E-1414A4BDED94",
								   "BEEF6007-CDE7-43EE-ACEB-655E0F5BB24C"
								   "4DDA5524-5B3C-491B-9A99-C90DDF3201AB");

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
Dictionary::Dictionary(const string& name,
			   		   const string& lang,
			   		   const string& cset,
			   		   const string& font) :
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
bool Dictionary::AddWord(const Word& word, const Category& category)
{
	if (!ContainsCategory(category))
		return false;
	return m_CategoryMap[category.GetName()].AddWord(word);
}

bool Dictionary::AddWords(const TWordVec& words, const Category& category)
{
	if (!ContainsCategory(category))
		return false;
	return m_CategoryMap[category.GetName()].AddWords(words);
}

bool Dictionary::RemoveWord(const Word& word)
{
	bool some = false;
	for_each(m_CategoryMap.begin(), m_CategoryMap.end(),
			 [&some, &word] (pair<const string, Category>& kv)
			 {
			 	if (kv.second.RemoveWord(word))
			 		some = true;
			 });
	return some;
}

bool Dictionary::RemoveWords(const TWordVec& words)
{
	return all_of(words.begin(), words.end(),
				  [&] (const Word& w) { return RemoveWord(w); } );
}

bool Dictionary::AddCategory(const Category& category)
{
	if (!category.IsValid() || ContainsCategory(category))
		return false;
	m_CategoryMap[category.GetName()] = category;
	return true;
}

bool Dictionary::AddCategories(const TCategoryVec& categories)
{
	return all_of(categories.begin(), categories.end(),
				  [&] (const Category& c) { return AddCategory(c); } );
}

bool Dictionary::RemoveCategory(const Category& category)
{
	if (!ContainsCategory(category))
		return false;
	return m_CategoryMap.erase(category.GetName()) == 1;
}

bool Dictionary::RemoveCategories(const TCategoryVec& categories)
{
	return all_of(categories.begin(), categories.end(),
				  [&] (const Category& c) { return RemoveCategory(c); } );
}

void Dictionary::Clear()
{
	m_CategoryMap.clear();
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
string Dictionary::GetName() 		 const { return m_Name; 		}
string Dictionary::GetLanguage() 	 const { return m_Lang; 		}
string Dictionary::GetCharacterSet() const { return m_CharacterSet;	}
string Dictionary::GetFont() 		 const { return m_Font; 		}

void Dictionary::SetName(const string& name)	  	 { m_Name = name; 		  }
void Dictionary::SetLanguage(const string& lang)  	 { m_Lang = lang;  		  }
void Dictionary::SetCharacterSet(const string& cset) { m_CharacterSet = cset; }
void Dictionary::SetFont(const string& font)		 { m_Font = font; 		  }

UI32 Dictionary::GetWordCount() const
{
	UI32 wc = 0;
	for_each(m_CategoryMap.begin(), m_CategoryMap.end(),
			 [&wc] (pair<const string, Category> kv) { wc += kv.second.GetWordCount(); });
	return wc;
}

UI32 Dictionary::GetCategoryCount() const { return m_CategoryMap.size(); }

// =============================================================================
//	QUESTION METHODS
// =============================================================================
bool Dictionary::IsEmpty() const { return m_CategoryMap.empty(); }

bool Dictionary::IsValid() const
{
	return m_Name 		  != InvalidDictionary.m_Name 		  ||
		   m_Lang 		  != InvalidDictionary.m_Lang 		  ||
		   m_CharacterSet != InvalidDictionary.m_CharacterSet ||
		   m_Font		  != InvalidDictionary.m_Font;
}

bool Dictionary::ContainsWord(const Word& word) const
{
	return any_of(m_CategoryMap.begin(), m_CategoryMap.end(),
				  [&word] (const pair<const string, const Category>& kv)
				  { return kv.second.ContainsWord(word); });
}

bool Dictionary::ContainsAllWords(const TWordVec& words) const
{
	return all_of(words.begin(), words.end(),
				  [&] (const Word& w) { return ContainsWord(w); });
}

bool Dictionary::ContainsCategory(const Category& category) const
{
	return m_CategoryMap.count(category.GetName()) == 1;
}

bool Dictionary::ContainsAllCategories(const TCategoryVec& categories) const
{
	return all_of(categories.begin(), categories.end(),
				  [&] (const Category& c) { return ContainsCategory(c); });
}

// =============================================================================
//	DEBUG METHODS
// =============================================================================
void Dictionary::PrintDebug(const string& spaces) const
{
	cout << spaces << "DICTIONARY" << endl;
	cout << spaces << "  Name:          \"" << m_Name << "\"" << endl;
	cout << spaces << "  Language:      \"" << m_Lang << "\"" << endl;
	cout << spaces << "  Character Set: \"" << m_CharacterSet << "\"" << endl;
	cout << spaces << "  Font:          \"" << m_Font << "\"" << endl;
	cout << spaces << "  Categories:" << endl;

	for (auto& kv : m_CategoryMap)
		kv.second.PrintDebug(spaces + "  ");
}

}
