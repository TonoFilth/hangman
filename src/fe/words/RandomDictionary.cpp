#include "fe/words/RandomDictionary.h"

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
RandomDictionary::RandomDictionary(const sf::String& characterSet, const std::string& fontFile,
	const TCategoryList& categoryList) :
	Dictionary(characterSet, fontFile, categoryList)
{
	srand(time(0));
}

RandomDictionary::~RandomDictionary()
{
}

// =============================================================================
//	PRIVATE AND PROTECTED METHODS
// =============================================================================
void RandomDictionary::ShuffleAll()
{
	for (auto& kv : m_IndexMap)
		ShuffleCategory(kv.first);
}

void RandomDictionary::ShuffleCategory(const TCategory& category)
{
	auto wc = GetWordCountByCategory(category);
	
	if (wc == 0)
		return;
	
	m_IndexMap[category].clear();

	for (UI32 i = 0; i < wc; ++i)
		m_IndexMap[category].push_back(i);

	random_shuffle(m_IndexMap[category].begin(), m_IndexMap[category].end());
}

// =============================================================================
//	VIRTUAL METHODS
// =============================================================================
Word RandomDictionary::GetWord(const TCategory& category, const UI32 index)
{
	if (m_IndexMap.count(category) == 0 || m_IndexMap[category].empty())
		return InvalidWord;

	UI32 idx = m_IndexMap[category].front();
	m_IndexMap.erase(m_IndexMap.begin());

	return Dictionary::GetWord(category, idx);
}

void RandomDictionary::AddWord(const Word& word, const TCategory& category)
{
	if (m_IndexMap.count(category) == 0)
		m_IndexMap[category] = TRandomIndexVec();

	ShuffleCategory(category);
	Dictionary::AddWord(word, category);
}

}
