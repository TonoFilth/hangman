#include "fe/db/BaseSqliteDAO.h"

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
BaseSqliteDAO::BaseSqliteDAO(const TDatabasePtr& db) :
	m_DB(db)
{
}

BaseSqliteDAO::~BaseSqliteDAO()
{
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
bool BaseSqliteDAO::DoSQL(const TSQLPredicate& predicate)
{
	if (predicate == nullptr)
		return false;

	bool pOut = false;

	try
	{
		pOut = predicate(SQLiteStatement(m_DB.get()));
	}
	catch (const SQLiteException& ex)
	{
		ex.Show();
		return false;
	}

	return pOut;
}

bool BaseSqliteDAO::DoSQLTransaction(const TSQLTransactionPredicate& predicate)
{
	if (predicate == nullptr)
		return false;

	SQLiteStatement transaction(m_DB.get());
	transaction.BeginTransaction();

	try
	{
		if (!predicate(transaction))
		{
			transaction.RollbackTransaction();
			return false;
		}
	}
	catch (const SQLiteException& ex)
	{
		ex.Show();
		transaction.RollbackTransaction();
		return false;
	}

	transaction.CommitTransaction();
	return true;
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
const TDatabasePtr& BaseSqliteDAO::GetDB() const { return m_DB; }

}
