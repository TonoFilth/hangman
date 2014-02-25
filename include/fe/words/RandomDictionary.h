#ifndef __RANDOM_DICTIONARY_H__
#define __RANDOM_DICTIONARY_H__

#include <algorithm>
#include <cstdlib>
#include <time.h>

#include "fe/words/Dictionary.h"

namespace fe
{

typedef std::vector<UI32> 					   TRandomIndexVec;
typedef std::map<TCategoryID, TRandomIndexVec> TRandomIndexMap;

class RandomDictionary : public Dictionary
{
private:
	TRandomIndexMap m_IndexMap;
	TRandomIndexVec m_RandomCategoryVec;

	bool ShuffleAll();
	bool ShuffleCategory(const TCategoryID categoryID);
	bool ShuffleRandomCategoryVector();

	Word GetWordFromAnyCategory();

	RandomDictionary(const RandomDictionary& toCopy);
	RandomDictionary& operator=(const RandomDictionary& toCopy);

public:
	RandomDictionary(const std::string& name,
			   		 const std::string& lang,
			   		 const std::string& characterSet,
			   		 const std::string& fontFile,
			   		 const TCategoryList& categoryList = TCategoryList());
	virtual ~RandomDictionary();

	virtual Word GetWord(const TCategoryID categoryID = AnyCategory.id,
						 const UI32 index = 0);
	virtual bool AddWord(const Word& word,
						 const TCategoryID categoryID = AnyCategory.id);
	virtual bool RemoveWord(const Word& word);
	virtual bool RemoveCategory(const TCategoryID categoryID);
};

}

#endif
