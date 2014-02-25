#include "fe/db/DictionaryDAOSqlite.h"

using namespace std;
using namespace sf;
using namespace Kompex;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
DictionaryDAOSqlite::DictionaryDAOSqlite(const TDatabasePtr& database) :
	m_Database(database)
{
}

DictionaryDAOSqlite::~DictionaryDAOSqlite()
{
}

// =============================================================================
//	VIRTUAL METHODS
// =============================================================================
TDictionaryID DictionaryDAOSqlite::InsertDictionary(const string& name,
										   			const string& lang,
										   			const string& characterSet,
								   		   			const string& fontFile)
{
	if (Exists(name))
	{
		cerr << "A dictionary with name " << name << " already exists" << endl;
		return INVALID_DICTIONARY_ID;
	}

	SQLiteStatement s(m_Database.get());

	try
	{
		s.Sql("INSERT INTO Dictionaries(name, lang, character_set, font_file) VALUES(@name, @lang, @character_set, @font_file)");

		s.BindString(1, name);
		s.BindString(2, lang);
		s.BindString(3, characterSet);
		s.BindString(4, fontFile);
		s.FetchRow();
	}
	catch (SQLiteException& ex)
	{
		ex.Show();
		s.FreeQuery();
		return INVALID_DICTIONARY_ID;
	}

	s.FreeQuery();
	return m_Database->GetLastInsertRowId();
}

TDictionaryPtr DictionaryDAOSqlite::GetDictionaryByID(const TDictionaryID id)
{
	TDictionaryPtr dictionary = nullptr;
	SQLiteStatement s(m_Database.get());

	try
	{
		s.Sql("SELECT * FROM Dictionaries WHERE id=@id");
		s.BindInt(1, id);

		if (s.FetchRow())
			dictionary = make_shared<SqliteDictionary>(s.GetColumnInt(0),
													   s.GetColumnString(1),
													   s.GetColumnString(2),
													   s.GetColumnString(3),
													   s.GetColumnString(4));
	}
	catch (SQLiteException& ex)
	{
		ex.Show();
		s.FreeQuery();
		return nullptr;
	}

	return dictionary;
}

TDictionaryList DictionaryDAOSqlite::GetAllDictionaries()
{
	TDictionaryList list;
	SQLiteStatement s(m_Database.get());

	try
	{
		s.Sql("SELECT * FROM Dictionaries");

		while (s.FetchRow())
			list.push_back(make_shared<SqliteDictionary>(s.GetColumnInt(0),
													   	 s.GetColumnString(1),
													   	 s.GetColumnString(2),
													   	 s.GetColumnString(3),
													   	 s.GetColumnString(4)));
	}
	catch (SQLiteException& ex)
	{
		ex.Show();
		s.FreeQuery();
		return list;
	}

	return list;
}

bool DictionaryDAOSqlite::Exists(const TDictionaryID id)
{
	SQLiteStatement s(m_Database.get());

	try
	{
		s.Sql("SELECT * FROM Dictionaries WHERE id=@id");
		s.BindInt(1, id);

		bool exists = s.FetchRow();
		s.FreeQuery();
		return exists;
	}
	catch (SQLiteException& ex)
	{
		ex.Show();
		s.FreeQuery();
		return false;
	}

	return false;
}

bool DictionaryDAOSqlite::Exists(const string& name)
{
	SQLiteStatement s(m_Database.get());

	try
	{
		s.Sql("SELECT * FROM Dictionaries WHERE name=@name");
		s.BindString(1, name);

		bool exists = s.FetchRow();
		s.FreeQuery();
		return exists;
	}
	catch (SQLiteException& ex)
	{
		ex.Show();
		s.FreeQuery();
		return false;
	}

	return false;
}

}
