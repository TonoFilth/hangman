#include "fe/db/DictionaryDAO.h"

using namespace std;

namespace fe
{

// =============================================================================
//	STATIC FIELDS
// =============================================================================
TIDictionaryDAOPtr DictionaryDAO::m_DAO = nullptr;

// =============================================================================
//	STATIC METHODS
// =============================================================================
TDictionaryID DictionaryDAO::InsertDictionary(const string& name,
										   	  const string& lang,
										      const string& characterSet,
										  	  const string& fontFile)
{
	return m_DAO->InsertDictionary(name, lang, characterSet, fontFile);
}

TDictionaryPtr DictionaryDAO::GetDictionaryByID(const TDictionaryID id)
{
	return m_DAO->GetDictionaryByID(id);
}

TDictionaryVec DictionaryDAO::GetAllDictionaries()
{
	return m_DAO->GetAllDictionaries();
}

bool DictionaryDAO::Exists(const TDictionaryID id)
{
	return m_DAO->Exists(id);
}

bool DictionaryDAO::Exists(const string& name)
{
	return m_DAO->Exists(name);
}

void DictionaryDAO::SetDAO(const TIDictionaryDAOPtr& dao)
{
	m_DAO = dao;
}

}