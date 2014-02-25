#ifndef __DICTIONARY_DAO_SQLITE_H__
#define __DICTIONARY_DAO_SQLITE_H__

#include "fe/db/DictionaryDAO.h"
#include "fe/words/SqliteDictionary.h"
#include "fe/types/PointerTypes.h"

namespace fe
{

class DictionaryDAOSqlite : public IDictionaryDAO
{
private:
	TDatabasePtr m_Database;

	DictionaryDAOSqlite(const DictionaryDAOSqlite& toCopy);
	DictionaryDAOSqlite& operator=(const DictionaryDAOSqlite& toCopy);

public:
	DictionaryDAOSqlite(const TDatabasePtr& database);
	virtual ~DictionaryDAOSqlite();

	virtual TDictionaryID InsertDictionary(const std::string& name,
										   const std::string& lang,
										   const std::string& characterSet,
								   		   const std::string& fontFile);
	virtual TDictionaryList GetAllDictionaries();
	virtual TDictionaryPtr GetDictionaryByID(const TDictionaryID id);

	virtual bool Exists(const TDictionaryID id);
	virtual bool Exists(const std::string& name);
};

}

#endif
