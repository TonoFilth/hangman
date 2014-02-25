#include "fe/db/WordDAO.h"

using namespace std;
using namespace sf;
using namespace Kompex;

namespace fe
{

// =============================================================================
//	STATIC FIELDS
// =============================================================================
TIWordDAOPtr WordDAO::m_DAO = nullptr;

// =============================================================================
//	STATIC METHODS
// =============================================================================
bool WordDAO::InsertWord(const TCategoryID categoryID, const Word& word)
{
	return m_DAO->InsertWord(categoryID, word);
}

TWordVec WordDAO::GetWordsByCategoryID(const TCategoryID categoryID)
{
	return m_DAO->GetWordsByCategoryID(categoryID);
}

void WordDAO::SetDAO(const TIWordDAOPtr& dao)
{
	m_DAO = dao;
}

}
