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

class Dictionary;
struct Category;

typedef UI32 							TDictionaryID;
typedef Category 					  	TCategory;
typedef UI32 						  	TCategoryID;
typedef std::list<TCategory> 		  	TCategoryList;
typedef std::list<TCategoryID>			TCategoryIDList;
typedef std::map<TCategoryID, TWordVec> TWordMap;
typedef std::shared_ptr<Dictionary>	  	TDictionaryPtr;
typedef std::list<TDictionaryPtr>		TDictionaryList;

extern const TDictionaryID INVALID_DICTIONARY_ID;
extern const TCategoryID INVALID_CATEGORY_ID;

extern const Category AnyCategory;
extern const Category InvalidCategory;

struct Category
{
	Category(const TCategoryID i, const std::string& n) :
		id(i), name(n)
	{
	}

	Category& operator=(const Category& toCopy)
	{
		if (this == &toCopy)
			return *this;

		id 	 = toCopy.id;
		name = toCopy.name;

		return *this;
	}

	TCategoryID  id;
	std::string  name;
};

class Dictionary
{
private:
	TWordMap    m_WordMap;
	std::string m_Name;
	std::string m_Lang;
	std::string m_CharacterSet;
	TFontPtr    m_Font;

	TCategoryID   m_CategoryID;
	TCategoryList m_Categories;

	Dictionary(const Dictionary& toCopy);
	Dictionary& operator=(const Dictionary& toCopy);

public:
	Dictionary(const std::string& name,
			   const std::string& lang,
			   const std::string& characterSet,
			   const std::string& fontFile,
			   const TCategoryList& categoryList = TCategoryList());
	virtual ~Dictionary();

	virtual Word GetWord(const TCategoryID categoryID = AnyCategory.id, const UI32 index = 0);
	virtual bool AddWord(const Word& word, const TCategoryID categoryID = AnyCategory.id);
	virtual TCategoryID AddCategory(const std::string& categoryName);
	virtual bool AddCategory(const TCategory& category);
	virtual bool RemoveWord(const Word& word);
	virtual bool RemoveCategory(const TCategoryID categoryID); 
	
	std::string GetName() const;
	std::string GetLanguage() const;

	UI32 GetWordCount() const;
	UI32 GetWordCountByCategory(const TCategoryID categoryID) const;
	UI32 GetCategoryCount() const;
	TCategoryList GetCategoryList() const;
	std::string GetCharacterSet() const;
	TFontPtr GetFont() const;

	bool IsEmpty() const;
	bool ContainsCategory(const TCategoryID categoryID) const;
};

}

#endif
