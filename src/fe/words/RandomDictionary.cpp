#include "fe/words/RandomDictionary.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
RandomDictionary::RandomDictionary(const string& name,
					   			   const string& lang,
					   			   const string& characterSet,
					   			   const string& fontFile,
					   			   const TCategoryList& categoryList) :
	Dictionary(name, lang, characterSet, fontFile, categoryList)
{
	srand(time(0));
}

RandomDictionary::~RandomDictionary()
{
}

// =============================================================================
//	PRIVATE AND PROTECTED METHODS
// =============================================================================
bool RandomDictionary::ShuffleAll()
{
	bool allOK = true;

	for (auto& kv : m_IndexMap)
		if (!ShuffleCategory(kv.first))
			allOK = false;

	return allOK;
}

bool RandomDictionary::ShuffleCategory(const TCategoryID categoryID)
{
	auto wc = GetWordCountByCategory(categoryID);
	
	if (wc == 0)
		return false;
	
	m_IndexMap[categoryID].clear();

	for (UI32 i = 0; i < wc; ++i)
		m_IndexMap[categoryID].push_back(i);

	random_shuffle(m_IndexMap[categoryID].begin(), m_IndexMap[categoryID].end());

	return true;
}

bool RandomDictionary::ShuffleRandomCategoryVector()
{
	auto cc = GetCategoryCount();

	if (cc == 0)
		return false;

	m_RandomCategoryVec.clear();

	for (auto& kv : m_IndexMap)
		m_RandomCategoryVec.push_back(kv.first);

	random_shuffle(m_RandomCategoryVec.begin(), m_RandomCategoryVec.end());	

	return true;
}

Word RandomDictionary::GetWordFromAnyCategory()
{
	if (m_RandomCategoryVec.empty() && !ShuffleRandomCategoryVector())
		return InvalidWord;

	UI32 categoryID = m_RandomCategoryVec.front();

	if (m_IndexMap[categoryID].empty() && !ShuffleCategory(categoryID))
		return InvalidWord;

	UI32 idx = m_IndexMap[categoryID].front();
	m_RandomCategoryVec.erase(m_RandomCategoryVec.begin());
	m_IndexMap[categoryID].erase(m_IndexMap[categoryID].begin());

	return Dictionary::GetWord(categoryID, idx);
}

// =============================================================================
//	VIRTUAL METHODS
// =============================================================================
Word RandomDictionary::GetWord(const TCategoryID categoryID, const UI32 index)
{
	if (categoryID == AnyCategory.id)
		return GetWordFromAnyCategory();

	if (m_IndexMap.count(categoryID) == 0)
		return InvalidWord;

	if (m_IndexMap[categoryID].empty() && !ShuffleCategory(categoryID))
		return InvalidWord;

	UI32 idx = m_IndexMap[categoryID].front();
	m_IndexMap[categoryID].erase(m_IndexMap[categoryID].begin());

	return Dictionary::GetWord(categoryID, idx);
}

bool RandomDictionary::AddWord(const Word& word, const TCategoryID categoryID)
{
	if (!ContainsCategory(categoryID))
		return false;

	if (m_IndexMap.count(categoryID) == 0)
		m_IndexMap[categoryID] = TRandomIndexVec();

	return Dictionary::AddWord(word, categoryID) && ShuffleCategory(categoryID);
}

bool RandomDictionary::RemoveWord(const Word& word)
{
	return Dictionary::RemoveWord(word) && ShuffleAll();
}

bool RandomDictionary::RemoveCategory(const TCategoryID categoryID)
{
	return (Dictionary::RemoveCategory(categoryID) && m_IndexMap.erase(categoryID) == 1);
}

}
