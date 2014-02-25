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
//	PRIVATE AND PROTECTED METHODS
// =============================================================================
TDictionaryPtr DictionaryDAOSqlite::CreateDictionary(const TDictionaryID id, const string& name,
													 const string& lang, const string& cset,
													 const string& fontFile)
{
	TFontPtr font = make_shared<Font>();

	if (!font->loadFromFile(fontFile))
		return nullptr;

	auto d = make_shared<Dictionary>(font, name, lang, cset);
	d->m_ID = id;

	return d;
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
		return InvalidDictionary.GetID();
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
		return InvalidDictionary.GetID();
	}

	s.FreeQuery();
	return m_Database->GetLastInsertRowId();
}

TDictionaryPtr DictionaryDAOSqlite::GetDictionaryByID(const TDictionaryID id)
{
	TDictionaryPtr dictionary(nullptr);
	SQLiteStatement s(m_Database.get());

	try
	{
		s.Sql("SELECT * FROM Dictionaries WHERE id=@id");
		s.BindInt(1, id);

		if (s.FetchRow() && (dictionary = CreateDictionary(s.GetColumnInt(0),
														   s.GetColumnString(1),
														   s.GetColumnString(2),
														   s.GetColumnString(3),
														   s.GetColumnString(4))) == nullptr)
		{
			cerr << "Can't create dictionary " << id << endl;
			s.FreeQuery();
			return nullptr;
		}
	}
	catch (SQLiteException& ex)
	{
		ex.Show();
		s.FreeQuery();
		return nullptr;
	}

	s.FreeQuery();
	return dictionary;
}

TDictionaryVec DictionaryDAOSqlite::GetAllDictionaries()
{
	TDictionaryVec dictionaries;
	TDictionaryPtr dictionary;

	SQLiteStatement s(m_Database.get());

	try
	{
		s.Sql("SELECT * FROM Dictionaries");

		while (s.FetchRow())
		{
			if ((dictionary = CreateDictionary(s.GetColumnInt(0),
											   s.GetColumnString(1),
											   s.GetColumnString(2),
											   s.GetColumnString(3),
											   s.GetColumnString(4))) == nullptr)
			{
				cerr << "Can't create dictionary " << s.GetColumnInt(0) << endl;
				s.FreeQuery();
				return TDictionaryVec();
			}

			dictionaries.push_back(dictionary);
		}
	}
	catch (SQLiteException& ex)
	{
		ex.Show();
		s.FreeQuery();
		return TDictionaryVec();
	}

	return dictionaries;
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
