#ifndef __IWORD_PROVIDER_H__
#define __IWORD_PROVIDER_H__

#include <list>
#include <map>

#include "fe/types/BasicTypes.h"
#include "fe/words/Word.h"

namespace fe
{

typedef sf::String 			 		  TCategory;
typedef std::list<TCategory> 		  TCategoryList;
typedef std::map<TCategory, TWordVec> TCategoryMap;
typedef std::vector<UI32>		 	  TRandomIndexVec;

class IWordProvider
{
private:
	IWordProvider(const IWordProvider& toCopy);
	IWordProvider& operator=(const IWordProvider& toCopy);

public:
	IWordProvider()			 {}
	virtual ~IWordProvider() {}

	virtual Word GetNextWord() = 0;
	virtual TCategoryList GetAvaliableCategories() const = 0;
	virtual TCategory GetCurrentCategory() const = 0;
	virtual sf::String GetCharacterList() const = 0;

	virtual void SetCurrentCategory(const TCategory& category) = 0;
};

}

#endif
