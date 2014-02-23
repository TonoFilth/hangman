#ifndef __WORD_DICTIONARY_H__
#define __WORD_DICTIONARY_H__

#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>

#include "fe/words/Word.h"
#include "fe/types/BasicTypes.h"
#include "fe/types/PointerTypes.h"

namespace fe
{

extern const std::string DEF_CATEGORY;

class Dictionary;

typedef sf::String 			 		  TCategory;
typedef std::list<TCategory> 		  TCategoryList;
typedef std::map<TCategory, TWordVec> TWordMap;
typedef std::shared_ptr<Dictionary>	  TDictionaryPtr;

class Dictionary
{
private:
	TWordMap   m_WordMap;
	sf::String m_CharacterSet;
	TFontPtr   m_Font;

	Dictionary(const Dictionary& toCopy);
	Dictionary& operator=(const Dictionary& toCopy);

public:
	Dictionary(const sf::String& characterSet, const std::string& fontFile,
		const TCategoryList& categoryList = TCategoryList());
	virtual ~Dictionary();

	virtual Word GetWord(const TCategory& category = DEF_CATEGORY, const UI32 index = 0);
	virtual void AddWord(const Word& word, const TCategory& category = DEF_CATEGORY);
	virtual void AddCategory(const TCategory& category);
	
	UI32 GetWordCount() const;
	UI32 GetWordCountByCategory(const TCategory& category) const;
	TCategoryList GetCategoryList() const;
	sf::String GetCharacterSet() const;
	TFontPtr GetFont() const;

	bool IsEmpty() const;
	bool ContainsCategory(const TCategory& category) const;
};

}

#endif
