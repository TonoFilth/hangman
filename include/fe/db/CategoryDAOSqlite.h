#ifndef __CATEGORY_DAO_SQLITE_H__
#define __CATEGORY_DAO_SQLITE_H__

#include <iostream>

#include "fe/db/DAOInterfaces.h"
#include "fe/db/BaseSqliteDAO.h"

namespace fe
{

class CategoryDAOSqlite : public CategoryDAO
{
private:
	BaseSqliteDAO m_Base;

	CategoryDAOSqlite(const CategoryDAOSqlite& toCopy);
	CategoryDAOSqlite& operator=(const CategoryDAOSqlite& toCopy);

public:
	CategoryDAOSqlite(const TDatabasePtr& db);
	virtual ~CategoryDAOSqlite();

	virtual QCategory Create(const std::string& name,
					  		 const TDictionaryID dicID);
	virtual bool	  Update(const QCategory& category);
	virtual bool	  Delete(const TCategoryID id);

	virtual QCategory GetByID(const TCategoryID catID);
	virtual QCategory GetByName(const std::string& name);
	
	virtual TQCategoryVec GetAll();
	virtual TQCategoryVec GetAllByDictionary(const TDictionaryID dicID);
	virtual TQCategoryVec GetIf(const TQCategoryPredicate& predicate);

	virtual bool Exists(const TCategoryID id);
	virtual bool Exists(const std::string& name);
};

}

#endif
