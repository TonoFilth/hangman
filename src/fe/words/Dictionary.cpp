#include "fe/words/Dictionary.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTANTS
// =============================================================================
const TDictionaryID INVALID_DICTIONARY_ID = 0;
const TCategoryID INVALID_CATEGORY_ID = 0;

const Category AnyCategory(666, "any");
const Category InvalidCategory(INVALID_CATEGORY_ID, "INVALID");

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
Dictionary::Dictionary(const string& name,
					   const string& lang,
					   const string& characterSet,
					   const string& fontFile,
					   const TCategoryList& categoryList) :
		m_Name(name),
		m_Lang(lang),
		m_CharacterSet(characterSet),
		m_Font(make_shared<Font>()),
		m_CategoryID(0)
{
	if (!m_Font->loadFromFile(fontFile))
	{
		cerr << "Can't load font " << fontFile << endl;
		throw;
	}

	for (auto& category : categoryList)
		m_WordMap[category.id] = TWordVec();
}

Dictionary::~Dictionary()
{
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
bool Dictionary::AddWord(const Word& word, const TCategoryID categoryID)
{
	if (m_WordMap.count(categoryID) == 0)
	{
		cerr << "Category " << categoryID << " doesn't exists" << endl;
		return false;
	}

	m_WordMap[categoryID].push_back(word);

	return true;
}

TCategoryID Dictionary::AddCategory(const string& categoryName)
{
	for (auto& category : m_Categories)
	{
		if (category.name == categoryName)
		{
			cerr << "Category " << categoryName << " already exists" << endl;
			return 0;
		}
	}

	TCategory category(m_CategoryID, categoryName);
	m_Categories.push_back(category);
	m_CategoryID++;
	m_WordMap[category.id] = TWordVec();

	return category.id;
}

bool Dictionary::AddCategory(const TCategory& category)
{
	if (m_WordMap.count(category.id) == 1)
	{
		cerr << "Category with id " << category.id << " already exists" << endl;
		return false;
	}

	m_WordMap[category.id] = TWordVec();
	return true;
}

bool Dictionary::RemoveWord(const Word& word)
{
	bool erased = false;

	for (auto& kv : m_WordMap)
	{
		for (auto it = kv.second.begin(); it != kv.second.end(); ++it)
		{
			if (*it == word)
			{
				kv.second.erase(it);
				erased = true;
				break;
			}
		}
	}

	return erased;
}

bool Dictionary::RemoveCategory(const TCategoryID categoryID)
{
	return m_WordMap.erase(categoryID) == 1;
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
string Dictionary::GetName() const
{
	return m_Name;
}

string Dictionary::GetLanguage() const
{
	return m_Lang;
}

Word Dictionary::GetWord(const TCategoryID categoryID, const UI32 index)
{
	if (m_WordMap.count(categoryID) == 0)
	{
		cerr << "Category " << categoryID << " doesn't exists" << endl;
		return Word();
	}

	if (m_WordMap[categoryID].size() <= index)
	{
		cerr << "Index out of range: " << index << endl;
		return Word();
	}

	return m_WordMap[categoryID][index];
}

UI32 Dictionary::GetWordCount() const
{
	UI32 wc = 0;

	for (auto& kv : m_WordMap)
		wc += kv.second.size();

	return wc;
}

UI32 Dictionary::GetWordCountByCategory(const TCategoryID categoryID) const
{
	if (m_WordMap.count(categoryID) == 0)
	{
		cerr << "Category " << categoryID << " doesn't exists" << endl;
		return 0;
	}

	return m_WordMap.find(categoryID)->second.size();
}

UI32 Dictionary::GetCategoryCount() const
{
	return m_Categories.size();
}

TCategoryList Dictionary::GetCategoryList() const
{
	return m_Categories;
}

string Dictionary::GetCharacterSet() const
{
	return m_CharacterSet;
}

TFontPtr Dictionary::GetFont() const
{
	return m_Font;
}

// =============================================================================
//	QUESTION METHODS
// =============================================================================
bool Dictionary::IsEmpty() const
{
	return m_WordMap.empty();
}

bool Dictionary::ContainsCategory(const TCategoryID categoryID) const
{
	return m_WordMap.count(categoryID) == 1;
}

}
