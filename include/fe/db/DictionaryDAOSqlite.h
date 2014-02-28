#ifndef __DICTIONARY_DAO_SQLITE_H__
#define __DICTIONARY_DAO_SQLITE_H__

#include "fe/db/DAOInterfaces.h"
#include "fe/db/BaseSqliteDAO.h"

namespace fe
{

class DictionaryDAOSqlite : public DictionaryDAO
{
private:
	BaseSqliteDAO m_Base;

	DictionaryDAOSqlite(const DictionaryDAOSqlite& toCopy);
	DictionaryDAOSqlite& operator=(const DictionaryDAOSqlite& toCopy);

public:
	DictionaryDAOSqlite(const TDatabasePtr& db);
	virtual ~DictionaryDAOSqlite();

	virtual QDictionary Create(const std::string& name,
							   const std::string& lang,
							   const std::string& cset,
							   const std::string& font);
	virtual bool Update(const QDictionary& dictionary);
	virtual bool Delete(const TDictionaryID dicID);

	virtual QDictionary GetByID(const TDictionaryID dicID);

	virtual TQDictionaryVec GetAll();
	virtual TQDictionaryVec GetIf(const TQDictionaryPredicate& predicate);

	virtual bool Exists(const TDictionaryID id);
	virtual bool Exists(const std::string& name);
};

}

#endif
