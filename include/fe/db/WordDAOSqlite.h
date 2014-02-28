#ifndef __WORD_DAO_SQLITE_H__
#define __WORD_DAO_SQLITE_H__

#include "fe/db/DAOInterfaces.h"
#include "fe/db/BaseSqliteDAO.h"
#include "fe/utils/StringUtils.h"

namespace fe
{

class WordDAOSqlite : public WordDAO
{
private:
	BaseSqliteDAO m_Base;

	WordDAOSqlite(const WordDAOSqlite& toCopy);
	WordDAOSqlite& operator=(const WordDAOSqlite& toCopy);

public:
	WordDAOSqlite(const TDatabasePtr& db);
	virtual ~WordDAOSqlite();

	virtual QWord Create(const TCategoryID catID,
						 const std::string& str,
						 const std::string& hint);
	virtual bool  Update(const QWord& word);
	virtual bool  Delete(const TWordID id);

	virtual TQWordVec GetIf(const TQWordPredicate& predicate);

	virtual TQWordVec GetAll();
	virtual TQWordVec GetAllByCategory(const TCategoryID catID);

	virtual bool Exists(const TWordID id);
	virtual bool Exists(const std::string& word);
};

}

#endif
