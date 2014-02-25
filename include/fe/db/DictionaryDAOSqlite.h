#ifndef __DICTIONARY_DAO_SQLITE_H__
#define __DICTIONARY_DAO_SQLITE_H__

#include "fe/db/DictionaryDAO.h"

namespace fe
{

class DictionaryDAOSqlite : public IDictionaryDAO
{
private:
	TDatabasePtr m_Database;

	TDictionaryPtr CreateDictionary(const TDictionaryID id, const std::string& name,
					 			    const std::string& lang, const std::string& cset,
					 				const std::string& fontFile);

	DictionaryDAOSqlite(const DictionaryDAOSqlite& toCopy);
	DictionaryDAOSqlite& operator=(const DictionaryDAOSqlite& toCopy);

public:
	DictionaryDAOSqlite(const TDatabasePtr& database);
	virtual ~DictionaryDAOSqlite();

	virtual TDictionaryID InsertDictionary(const std::string& name,
										   const std::string& lang,
										   const std::string& characterSet,
								   		   const std::string& fontFile);
	virtual TDictionaryVec GetAllDictionaries();
	virtual TDictionaryPtr GetDictionaryByID(const TDictionaryID id);

	virtual bool Exists(const TDictionaryID id);
	virtual bool Exists(const std::string& name);
};

}

#endif
