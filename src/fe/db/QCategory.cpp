#include "fe/db/QCategory.h"

using namespace std;

namespace fe
{

// =============================================================================
//	CONSTANTS
// =============================================================================
const TCategoryID ERR_CATEGORY_ID = 0;

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
QCategory::QCategory(const TCategoryID id, const string& name) :
	Category(name),
	m_ID(id)
{
}

QCategory::QCategory(const QCategory& toCopy) : Category(toCopy)
{
	m_ID = toCopy.m_ID;
}

QCategory& QCategory::operator=(const QCategory& toCopy)
{
	if (this == &toCopy)
		return *this;

	Category::operator=(toCopy);
	m_ID = toCopy.m_ID;
	
	return *this;
}

QCategory::~QCategory()
{
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
TCategoryID QCategory::GetID() const { return m_ID; }

}
