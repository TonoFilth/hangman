#ifndef __WORD_DAO_SQLITE_H__
#define __WORD_DAO_SQLITE_H__

#include "fe/db/WordDAO.h"
#include "fe/utils/StringUtils.h"

namespace fe
{

class WordDAOSqlite : public IWordDAO
{
private:
	TDatabasePtr m_Database;

	WordDAOSqlite(const WordDAOSqlite& toCopy);
	WordDAOSqlite& operator=(const WordDAOSqlite& toCopy);

public:
	WordDAOSqlite(const TDatabasePtr& database);
	virtual ~WordDAOSqlite();

	virtual bool InsertWord(const TCategoryID categoryID, const Word& word);
	virtual TWordVec GetWordsByCategoryID(const TCategoryID categoryID);
};

}

#endif
