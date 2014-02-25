#include "fe/db/CategoryDAOSqlite.h"

using namespace std;
using namespace sf;
using namespace Kompex;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
CategoryDAOSqlite::CategoryDAOSqlite(const TDatabasePtr& database) :
	m_Database(database)
{
}

CategoryDAOSqlite::~CategoryDAOSqlite()
{
}

// =============================================================================
//	VIRTUAL METHODS
// =============================================================================
TCategoryID CategoryDAOSqlite::InsertCategory(const TDictionaryID dictionaryID,
									   		  const string& name)
{
	if (Exists(name))
	{
		cerr << "Category " << name << " already exists" << endl;
		return INVALID_CATEGORY_ID;
	}

	if (!DictionaryDAO::Exists(dictionaryID))
	{
		cerr << "Dictionary with id " << dictionaryID << " doesn't exits" << endl;
		return INVALID_CATEGORY_ID;
	}

	SQLiteStatement s(m_Database.get());

	try
	{
		s.Sql("INSERT INTO Categories(name) VALUES(@name)");
		s.BindString(1, name);
		s.FetchRow();

		auto categoryID = m_Database->GetLastInsertRowId();
		s.FreeQuery();

		s.Sql("INSERT INTO DictionaryCategories(dictionary_id, category_id) VALUES(@did, @cid)");
		s.BindInt(1, dictionaryID);
		s.BindInt(2, categoryID);
		s.FetchRow();

		s.FreeQuery();
		return categoryID;
	}
	catch (SQLiteException& ex)
	{
		ex.Show();
		s.FreeQuery();
		return INVALID_CATEGORY_ID;
	}

	s.FreeQuery();
	return INVALID_CATEGORY_ID;
}

TCategory CategoryDAOSqlite::GetCategoryByID(const TCategoryID id)
{
	SQLiteStatement s(m_Database.get());

	try
	{
		s.Sql("SELECT * FROM Categories WHERE id=@id");
		s.BindInt(1, id);

		if (!s.FetchRow())
			return InvalidCategory;

		TCategory c(s.GetColumnInt(0), s.GetColumnString(1));
		s.FreeQuery();
		return c;
	}
	catch (SQLiteException& ex)
	{
		ex.Show();
		s.FreeQuery();
		return InvalidCategory;
	}

	return InvalidCategory;
}

TCategoryList CategoryDAOSqlite::GetCategoriesByDictionaryID(const TDictionaryID id)
{
	if (!DictionaryDAO::Exists(id))
	{
		cerr << "Dictionary with id " << id << " doesn't exists" << endl;
		return TCategoryList();
	}

	TCategoryList list;
	SQLiteStatement s(m_Database.get());

	try
	{
		s.Sql("SELECT Categories.id, Categories.name FROM Categories, DictionaryCategories WHERE DictionaryCategories.dictionary_id=@did AND DictionaryCategories.category_id=Categories.id");
		s.BindInt(1, id);

		while (s.FetchRow())
			list.push_back(TCategory(s.GetColumnInt(0), s.GetColumnString(1)));
	}
	catch (SQLiteException& ex)
	{
		ex.Show();
		s.FreeQuery();
		return TCategoryList();
	}

	s.FreeQuery();
	return list;
}

bool CategoryDAOSqlite::Exists(const TCategoryID id)
{
	SQLiteStatement s(m_Database.get());

	try
	{
		s.Sql("SELECT * FROM Categories WHERE id=@id");
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

bool CategoryDAOSqlite::Exists(const string& name)
{
	SQLiteStatement s(m_Database.get());

	try
	{
		s.Sql("SELECT * FROM Categories WHERE name=@name");
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
