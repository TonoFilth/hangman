#ifndef __BASE_SQLITE_DAO_H__
#define __BASE_SQLITE_DAO_H__

#include <functional>

#include "Kompex/KompexSQLiteDatabase.h"
#include "Kompex/KompexSQLiteStatement.h"
#include "Kompex/KompexSQLiteException.h"

#include "fe/types/PointerTypes.h"

using namespace Kompex;

namespace fe
{

typedef std::function<bool(SQLiteStatement)>  TSQLPredicate;
typedef std::function<bool(SQLiteStatement&)> TSQLTransactionPredicate;

class BaseSqliteDAO
{
private:
	TDatabasePtr m_DB;

	BaseSqliteDAO(const BaseSqliteDAO& toCopy);
	BaseSqliteDAO& operator=(const BaseSqliteDAO& toCopy);

public:
	BaseSqliteDAO(const TDatabasePtr& db);
	virtual ~BaseSqliteDAO();

	bool DoSQL(const TSQLPredicate& predicate);
	bool DoSQLTransaction(const TSQLTransactionPredicate& predicate);

	const TDatabasePtr& GetDB() const;
};

}

#endif
