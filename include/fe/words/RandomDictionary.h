#ifndef __RANDOM_DICTIONARY_H__
#define __RANDOM_DICTIONARY_H__

#include <algorithm>
#include <cstdlib>
#include <time.h>

#include "fe/words/Dictionary.h"

namespace fe
{

typedef std::vector<UI32> 					 TRandomIndexVec;
typedef std::map<TCategory, TRandomIndexVec> TRandomIndexMap;

class RandomDictionary : public Dictionary
{
private:
	TRandomIndexMap m_IndexMap;

	void ShuffleAll();
	void ShuffleCategory(const TCategory& category);

	RandomDictionary(const RandomDictionary& toCopy);
	RandomDictionary& operator=(const RandomDictionary& toCopy);

public:
	RandomDictionary(const sf::String& characterSet, const std::string& fontFile,
		const TCategoryList& categoryList = TCategoryList());
	virtual ~RandomDictionary();

	virtual Word GetWord(const TCategory& category = DEF_CATEGORY, const UI32 index = 0);
	virtual void AddWord(const Word& word, const TCategory& category = DEF_CATEGORY);
};

}

#endif
