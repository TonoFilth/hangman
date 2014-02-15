#include "fe/words/StubWordProvider.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
StubWordProvider::StubWordProvider() :
	m_CurrentCategory(L"default")
{
	TWordVec defVec;
	TWordVec farmVec;

	defVec.push_back(Word(L"ELECTRONIC CIGARETTE",L""));
	defVec.push_back(Word(L"COMPUTER",L""));
	defVec.push_back(Word(L"WALLET",L""));

	farmVec.push_back(Word(L"HEN",L""));
	farmVec.push_back(Word(L"PIG",L""));

	m_CategoryMap["default"] = defVec;
	m_CategoryMap["farm"] 	 = farmVec;
	m_CategoryMap["empty"] = TWordVec();

	srand(time(0));
	ShuffleWords();
}

StubWordProvider::~StubWordProvider()
{
}

// =============================================================================
//	PRIVATE AND PROTECTED METHODS
// =============================================================================
void StubWordProvider::ShuffleWords()
{
	if (m_CategoryMap.count(m_CurrentCategory) == 0)
		return;

	m_RandomIndexVec.clear();

	for (UI32 i = 0; i < m_CategoryMap[m_CurrentCategory].size(); ++i)
		m_RandomIndexVec.push_back(i);

	random_shuffle(m_RandomIndexVec.begin(), m_RandomIndexVec.end());
}

// =============================================================================
//	VIRTUAL METHODS
// =============================================================================
Word StubWordProvider::GetNextWord()
{
	if (m_RandomIndexVec.empty())
		ShuffleWords();

	// No words in the current category
	if (m_RandomIndexVec.empty())
	{
		cerr << "ERROR! There aren't words in the " << m_CurrentCategory.toAnsiString() << " category" << endl;
		return Word(L"ERROR", L"ERROR");
	}

	Word w(m_CategoryMap[m_CurrentCategory][m_RandomIndexVec.front()]);
	m_RandomIndexVec.erase(m_RandomIndexVec.begin());

	return w;
}

TCategoryList StubWordProvider::GetAvaliableCategories() const
{
	TCategoryList categoryList;

	for (auto& kv : m_CategoryMap)
		categoryList.push_back(kv.first);

	return categoryList;
}

TCategory StubWordProvider::GetCurrentCategory() const
{
	return m_CurrentCategory;
}

String StubWordProvider::GetCharacterList() const
{
	return String(L"ABCDEFGHIJKLMNÑOPQRSTUVWXYZ");
}

void StubWordProvider::SetCurrentCategory(const TCategory& category)
{
	if (m_CategoryMap.count(category) == 0)
	{
		cerr << "Category " << category.toAnsiString() << " doesn't exists" << endl;
		return;
	}

	m_CurrentCategory = category;
	ShuffleWords();
}

}
