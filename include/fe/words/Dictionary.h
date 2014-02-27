#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <memory>
#include "fe/words/Category.h"

namespace fe
{

class Dictionary;

typedef std::shared_ptr<Dictionary> TDictionaryPtr;
typedef std::vector<TDictionaryPtr>	TDictionaryVec;

extern const std::string DEF_DICTIONARY_NAME;
extern const std::string DEF_DICTIONARY_LANG;
extern const std::string DEF_DICTIONARY_CHARACTER_SET;
extern const std::string DEF_DICTIONARY_FONT;
extern const Dictionary  InvalidDictionary;

class Dictionary
{
private:
	std::string   m_Name;
	std::string   m_Lang;
	std::string   m_CharacterSet;
	std::string   m_Font;
	TCategoryMap  m_CategoryMap;

	Dictionary(const Dictionary& toCopy);
	Dictionary& operator=(const Dictionary& toCopy);

public:
	Dictionary(const std::string& name = DEF_DICTIONARY_NAME,
			   const std::string& lang = DEF_DICTIONARY_LANG,
			   const std::string& cset = DEF_DICTIONARY_CHARACTER_SET,
			   const std::string& font = DEF_DICTIONARY_FONT);
	virtual ~Dictionary();

	bool AddWord(const Word& word, const Category& category);
	bool AddWords(const TWordVec& words, const Category& category);
	bool RemoveWord(const Word& word);
	bool RemoveWords(const TWordVec& words);

	bool AddCategory(const Category& category);
	bool AddCategories(const TCategoryVec& categories);
	bool RemoveCategory(const Category& category);
	bool RemoveCategories(const TCategoryVec& categories);

	void Clear();

	std::string GetName() 		  const;
	std::string GetLanguage() 	  const;
	std::string GetCharacterSet() const;
	std::string	GetFont() 		  const;

	void SetName(const std::string& name);
	void SetLanguage(const std::string& lang);
	void SetCharacterSet(const std::string& cset);
	void SetFont(const std::string& font);

	UI32 GetWordCount() const;
	UI32 GetCategoryCount() const;

	bool IsEmpty() const;
	bool IsValid() const;
	bool ContainsWord(const Word& word) const;
	bool ContainsAllWords(const TWordVec& word) const;
	bool ContainsCategory(const Category& categoryName) const;
	bool ContainsAllCategories(const TCategoryVec& categories) const;

	void PrintDebug(const std::string& spaces = "") const;
};

}

#endif
