#ifndef __CATEGORY_DAO_SQLITE_H__
#define __CATEGORY_DAO_SQLITE_H__

#include "fe/db/CategoryDAO.h"

namespace fe
{

class CategoryDAOSqlite : public ICategoryDAO
{
private:
	TDatabasePtr m_Database;

	CategoryDAOSqlite(const CategoryDAOSqlite& toCopy);
	CategoryDAOSqlite& operator=(const CategoryDAOSqlite& toCopy);

public:
	CategoryDAOSqlite(const TDatabasePtr& database);
	virtual ~CategoryDAOSqlite();

	virtual TCategoryID InsertCategory(const TDictionaryID dictionaryID,
									   const std::string& name);
	virtual TCategory GetCategoryByID(const TCategoryID id);
	virtual TCategoryList GetCategoriesByDictionaryID(const TDictionaryID id);

	virtual bool Exists(const TCategoryID id);
	virtual bool Exists(const std::string& name);
};

}

#endif
