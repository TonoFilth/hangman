#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include "fe/words/Category.h"
#include "fe/types/PointerTypes.h"

namespace fe
{

class Dictionary;
class DictionaryDAOSqlite;

typedef UI32 						TDictionaryID;
typedef std::shared_ptr<Dictionary> TDictionaryPtr;
typedef std::vector<TDictionaryPtr>	TDictionaryVec;

extern const std::string DEF_DICTIONARY_NAME;
extern const std::string DEF_DICTIONARY_LANG;
extern const std::string DEF_DICTIONARY_CHARACTER_SET;
extern const TDictionaryID ERR_DICTIONARY_ID;
extern const Dictionary InvalidDictionary;

class Dictionary
{
private:
	friend class DictionaryDAOSqlite;
	static TDictionaryID DICTIONARY_ID;

	TDictionaryID m_ID;
	std::string   m_Name;
	std::string   m_Lang;
	std::string   m_CharacterSet;
	TFontPtr      m_Font;
	TCategoryMap  m_CategoryMap;

	Dictionary(const Dictionary& toCopy);
	Dictionary& operator=(const Dictionary& toCopy);

public:
	Dictionary(const TFontPtr& font,
			   const std::string& name = DEF_DICTIONARY_NAME,
			   const std::string& lang = DEF_DICTIONARY_LANG,
			   const std::string& cset = DEF_DICTIONARY_CHARACTER_SET);
	virtual ~Dictionary();

	void AddCategory(const Category& category);
	void AddCategories(const TCategoryVec& categories);
	void RemoveCategory(const Category& category);
	void RemoveCategories(const TCategoryVec& categories);

	TDictionaryID GetID() 			const;
	std::string   GetName() 		const;
	std::string   GetLanguage() 	const;
	std::string   GetCharacterSet() const;
	TFontPtr	  GetFont() 		const;

	void SetName(const std::string& name);
	void SetLanguage(const std::string& lang);
	void SetCharacterSet(const std::string& cset);
	void SetFont(const TFontPtr& font);

	bool IsEmpty() const;
	bool IsValid() const;
	bool ContainsCategory(const Category& category) const;
	bool ContainsWord(const Word& word) const;

	void PrintDebug(const std::string& spaces = "") const;
};

}

#endif
