#include "fe/db/CategoryDAOSqlite.h"

using namespace std;
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
//	PRIVATE AND PROTECTED METHODS
// =============================================================================
Category CategoryDAOSqlite::CreateCategory(const TCategoryID id,
										   const string& name)
{
	Category category(name);
	category.m_ID = id;
	return category;
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
		return InvalidCategory.GetID();
	}

	if (!DictionaryDAO::Exists(dictionaryID))
	{
		cerr << "Dictionary with id " << dictionaryID << " doesn't exits" << endl;
		return InvalidCategory.GetID();
	}

	SQLiteStatement s(m_Database.get());
	TCategoryID categoryID = InvalidCategory.GetID();

	try
	{
		s.Sql("INSERT INTO Categories(name) VALUES(@name)");
		s.BindString(1, name);
		s.FetchRow();

		categoryID = m_Database->GetLastInsertRowId();
		s.FreeQuery();

		s.Sql("INSERT INTO DictionaryCategories(dictionary_id, category_id) VALUES(@did, @cid)");
		s.BindInt(1, dictionaryID);
		s.BindInt(2, categoryID);
		s.FetchRow();
	}
	catch (SQLiteException& ex)
	{
		ex.Show();
		s.FreeQuery();
		return InvalidCategory.GetID();
	}
	
	s.FreeQuery();
	return categoryID;
}

Category CategoryDAOSqlite::GetCategoryByID(const TCategoryID id)
{
	SQLiteStatement s(m_Database.get());
	Category category(InvalidCategory);

	try
	{
		s.Sql("SELECT * FROM Categories WHERE id=@id");
		s.BindInt(1, id);

		if (!s.FetchRow())
			return InvalidCategory;

		category = CreateCategory(s.GetColumnInt(0), s.GetColumnString(1));
	}
	catch (SQLiteException& ex)
	{
		ex.Show();
		s.FreeQuery();
		return InvalidCategory;
	}

	s.FreeQuery();
	return category;
}

TCategoryVec CategoryDAOSqlite::GetCategoriesByDictionaryID(const TDictionaryID id)
{
	if (!DictionaryDAO::Exists(id))
	{
		cerr << "Dictionary with id " << id << " doesn't exists" << endl;
		return TCategoryVec();
	}

	TCategoryVec categories;
	SQLiteStatement s(m_Database.get());

	try
	{
		s.Sql("SELECT Categories.id, Categories.name FROM Categories, DictionaryCategories WHERE DictionaryCategories.dictionary_id=@did AND DictionaryCategories.category_id=Categories.id");
		s.BindInt(1, id);

		while (s.FetchRow())
			categories.push_back(CreateCategory(s.GetColumnInt(0), s.GetColumnString(1)));
	}
	catch (SQLiteException& ex)
	{
		ex.Show();
		s.FreeQuery();
		return TCategoryVec();
	}

	s.FreeQuery();
	return categories;
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
