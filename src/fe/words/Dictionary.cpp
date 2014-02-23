#include "fe/words/Dictionary.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTANTS
// =============================================================================
const string DEF_CATEGORY = "default";

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
Dictionary::Dictionary(const String& characterSet, const string& fontFile,
	const TCategoryList& categoryList) :
		m_CharacterSet(characterSet),
		m_Font(make_shared<Font>())
{
	if (!m_Font->loadFromFile(fontFile))
	{
		cerr << "Can't load font " << fontFile << endl;
		throw;
	}

	m_WordMap["default"] = TWordVec();

	for (auto& category : categoryList)
		m_WordMap[category] = TWordVec();
}

Dictionary::~Dictionary()
{
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
void Dictionary::AddWord(const Word& word, const TCategory& category)
{
	if (m_WordMap.count(category) == 0)
	{
		cerr << "Category " << category.toAnsiString() << " doesn't exists" << endl;
		return;
	}

	m_WordMap[category].push_back(word);
}

void Dictionary::AddCategory(const TCategory& category)
{
	if (m_WordMap.count(category) == 1)
	{
		cerr << "Category " << category.toAnsiString() << " already exists" << endl;
		return;
	}

	m_WordMap[category] = TWordVec();
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
Word Dictionary::GetWord(const TCategory& category, const UI32 index)
{
	if (m_WordMap.count(category) == 0)
	{
		cerr << "Category " << category.toAnsiString() << " doesn't exists" << endl;
		return Word();
	}

	if (m_WordMap[category].size() <= index)
	{
		cerr << "Index out of range: " << index << endl;
		return Word();
	}

	return m_WordMap[category][index];
}

UI32 Dictionary::GetWordCount() const
{
	UI32 wc = 0;

	for (auto& kv : m_WordMap)
		wc += kv.second.size();

	return wc;
}

UI32 Dictionary::GetWordCountByCategory(const TCategory& category) const
{
	if (m_WordMap.count(category) == 0)
	{
		cerr << "Category " << category.toAnsiString() << " doesn't exists" << endl;
		return 0;
	}

	return m_WordMap.find(category)->second.size();
}

String Dictionary::GetCharacterSet() const
{
	return m_CharacterSet;
}

TCategoryList Dictionary::GetCategoryList() const
{
	TCategoryList cl;

	for (auto& kv : m_WordMap)
		cl.push_back(kv.first);

	return cl;
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

bool Dictionary::ContainsCategory(const TCategory& category) const
{
	return m_WordMap.count(category) == 1;
}

}
