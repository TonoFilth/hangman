#include "fe/db/CategoryDAO.h"

using namespace std;

namespace fe
{

// =============================================================================
//	STATIC FIELDS
// =============================================================================
TICategoryDAOPtr CategoryDAO::m_DAO = nullptr;

// =============================================================================
//	STATIC METHODS
// =============================================================================
TCategoryID CategoryDAO::InsertCategory(const TDictionaryID dictionaryID,
									    const string& name)
{
	return m_DAO->InsertCategory(dictionaryID, name);
}

Category CategoryDAO::GetCategoryByID(const TCategoryID id)
{
	return m_DAO->GetCategoryByID(id);
}

TCategoryVec CategoryDAO::GetCategoriesByDictionaryID(const TDictionaryID id)
{
	return m_DAO->GetCategoriesByDictionaryID(id);
}

bool CategoryDAO::Exists(const TCategoryID id)
{
	return m_DAO->Exists(id);
}

bool CategoryDAO::Exists(const string& name)
{
	return m_DAO->Exists(name);
}

void CategoryDAO::SetDAO(const TICategoryDAOPtr& dao)
{
	m_DAO = dao;
}

}
