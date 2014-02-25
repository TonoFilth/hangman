#ifndef __SQLITE_DICTIONARY_H__
#define __SQLITE_DICTIONARY_H__

#include "fe/words/RandomDictionary.h"
#include "fe/db/DictionaryDAOSqlite.h"
#include "fe/db/CategoryDAOSqlite.h"
#include "fe/db/WordDAOSqlite.h"

namespace fe
{

class SqliteDictionary : public RandomDictionary
{
private:
	TDictionaryID m_ID;

	void LoadCategories();
	bool LoadCategory(const TCategoryID categoryID);
	void LoadWords(const TCategoryID categoryID);

	SqliteDictionary(const SqliteDictionary& toCopy);
	SqliteDictionary& operator=(const SqliteDictionary& toCopy);

public:
	SqliteDictionary(const TDictionaryID id,
					 const std::string& name,
					 const std::string& lang,
					 const std::string& characterSet,
					 const std::string& fontFile,
					 const TCategoryList& categoryList = TCategoryList());
	~SqliteDictionary();

	virtual Word GetWord(const TCategoryID categoryID = AnyCategory.id,
						 const UI32 index = 0);
	virtual bool AddWord(const Word& word, const TCategoryID categoryID = AnyCategory.id);
	virtual TCategoryID AddCategory(const std::string& categoryName);
	virtual bool RemoveWord(const Word& word);
	virtual bool RemoveCategory(const TCategoryID categoryID); 
};

}

#endif
