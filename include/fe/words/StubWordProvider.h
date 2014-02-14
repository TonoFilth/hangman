#ifndef __STUB_WORD_PROVIDER_H__
#define __STUB_WORD_PROVIDER_H__

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <time.h>

#include "fe/words/IWordProvider.h"

namespace fe
{

class StubWordProvider : public IWordProvider
{
private:
	TCategory 	 	 m_CurrentCategory;
	TCategoryMap 	 m_CategoryMap;
	TRandomIndexVec  m_RandomIndexVec;

	void ShuffleWords();

	StubWordProvider(const StubWordProvider& toCopy);
	StubWordProvider& operator=(const StubWordProvider& toCopy);

public:
	StubWordProvider();
	~StubWordProvider();

	virtual Word GetNextWord();
	virtual TCategoryList GetAvaliableCategories() const;
	virtual TCategory GetCurrentCategory() const;
	virtual sf::String GetCharacterList() const;

	virtual void SetCurrentCategory(const TCategory& category);
};

}

#endif
