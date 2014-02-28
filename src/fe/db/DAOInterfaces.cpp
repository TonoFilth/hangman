#include "fe/db/DAOInterfaces.h"

using namespace std;

namespace fe
{

// =============================================================================
//	STATIC FIELDS
// =============================================================================
TWordDAOPtr MasterDAO::Words 			  = nullptr;
TCategoryDAOPtr MasterDAO::Categories 	  = nullptr;
TDictionaryDAOPtr MasterDAO::Dictionaries = nullptr;

}