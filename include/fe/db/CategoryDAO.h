#ifndef __CATEGORY_DAO_H__
#define __CATEGORY_DAO_H__

#include "fe/db/DictionaryDAO.h"
#include "fe/words/Category.h"

namespace fe
{

class ICategoryDAO;

typedef std::shared_ptr<ICategoryDAO> TICategoryDAOPtr;

class ICategoryDAO
{
private:
	ICategoryDAO(const ICategoryDAO& toCopy);
	ICategoryDAO& operator=(const ICategoryDAO& toCopy);

public:
	ICategoryDAO() 		    {}
	virtual ~ICategoryDAO() {}

	virtual TCategoryID InsertCategory(const TDictionaryID dictionaryID,
									   const std::string& name) = 0;
	virtual Category GetCategoryByID(const TCategoryID id) = 0;
	virtual TCategoryVec GetCategoriesByDictionaryID(const TDictionaryID id) = 0;

	virtual bool Exists(const TCategoryID id) = 0;
	virtual bool Exists(const std::string& name) = 0;
};

class CategoryDAO
{
private:
	static TICategoryDAOPtr m_DAO;

	CategoryDAO();
	CategoryDAO(const CategoryDAO& toCopy);
	CategoryDAO& operator=(const CategoryDAO& toCopy);

public:
	virtual ~CategoryDAO() {}

	static TCategoryID InsertCategory(const TDictionaryID dictionaryID,
									  const std::string& name);
	static Category GetCategoryByID(const TCategoryID id);
	static TCategoryVec GetCategoriesByDictionaryID(const TDictionaryID id);

	static bool Exists(const TCategoryID id);
	static bool Exists(const std::string& name);

	static void SetDAO(const TICategoryDAOPtr& dao);
};

}

#endif
