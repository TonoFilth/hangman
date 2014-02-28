#ifndef __QUERYABLE_CATEGORY_H__
#define __QUERYABLE_CATEGORY_H__

#include "fe/words/Category.h"

namespace fe
{

class QCategory;

typedef UI32 				   TCategoryID;
typedef std::vector<QCategory> TQCategoryVec;

extern const TCategoryID ERR_CATEGORY_ID;

class QCategory : public Category
{
private:
	friend class CategoryDAO;
	
	TCategoryID m_ID;
	QCategory(const TCategoryID id, const std::string& name);

public:
	QCategory(const QCategory& toCopy);
	QCategory& operator=(const QCategory& toCopy);
	virtual ~QCategory();

	TCategoryID GetID() const;
};

}

#endif
