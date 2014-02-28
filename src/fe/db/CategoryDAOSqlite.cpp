#include "fe/db/CategoryDAOSqlite.h"

using namespace std;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
CategoryDAOSqlite::CategoryDAOSqlite(const TDatabasePtr& db) :
	m_Base(db)
{
}

CategoryDAOSqlite::~CategoryDAOSqlite()
{
}

// =============================================================================
//	VIRTUAL METHODS
// =============================================================================
QCategory CategoryDAOSqlite::Create(const string& name,
									const TCategoryID dicID)
{
	if (!MasterDAO::Dictionaries->Exists(dicID) || Exists(name))
		return InvalidQCategory;

	QCategory qc(InvalidQCategory);

	if (!m_Base.DoSQL([&dicID, &name, &qc, this] (SQLiteStatement s)
	{
		s.Sql("INSERT INTO Categories(name) VALUES(@name)");
		s.BindString(1, name);
		s.Execute();

		auto catID = m_Base.GetDB()->GetLastInsertRowId();
		if (catID == 0)
			return false;

		s.FreeQuery();
		s.Sql("INSERT INTO DictionaryCategories(dictionary_id, category_id) VALUES(@dicID, @catID)");
		s.BindInt(1, dicID);
		s.BindInt(2, catID);
		s.Execute();

		auto relationshipID = m_Base.GetDB()->GetLastInsertRowId();
		if (relationshipID > 0)
		{
			qc = CreateQCategory(catID, name);
			return true;
		}

		// Category inserted but insertion of relationship between Dictionary and
		// Category rejected. Try to delete the category to make the database
		// consistent
		return Delete(catID);
	}))
		return InvalidQCategory;

	return qc;
}

bool CategoryDAOSqlite::Update(const QCategory& category)
{
	if (!Exists(category.GetID()))
		return false;

	return m_Base.DoSQL([&category] (SQLiteStatement s)
	{
		s.Sql("UPDATE Categories SET name=@name WHERE id=@id");
		s.BindString(1, category.GetName());
		s.BindInt(2, category.GetID());
		s.Execute();

		return true;
	});
}

bool CategoryDAOSqlite::Delete(const TCategoryID catID)
{
	if (!Exists(catID))
		return false;

	return m_Base.DoSQL([&catID, this] (SQLiteStatement s)
	{
		// Delete words associated with this category
		auto words = MasterDAO::Words->GetAllByCategory(catID);

		for (auto word : words)
			if (!MasterDAO::Words->Delete(word.GetID()))
				cerr << "Word " << word.GetID() << " not deleted" << endl;

		// Retrieve dictionary ID associated with this category
		s.Sql("SELECT dictionary_id FROM DictionaryCategories WHERE category_id=@id");
		s.BindInt(1, catID);
		
		if (!s.FetchRow())
			return false;

		auto dicID = s.GetColumnInt(0);

		// Delete relationship between dictionary and category
		s.FreeQuery();
		s.Sql("DELETE FROM DictionaryCategories WHERE dictionary_id=@dicID AND category_id=@catID");
		s.BindInt(1, dicID);
		s.BindInt(2, catID);
		s.ExecuteAndFree();

		// Delete category
		s.Sql("DELETE FROM Categories WHERE id=@id");
		s.BindInt(1, catID);
		s.ExecuteAndFree();

		return true;
	});
}

QCategory CategoryDAOSqlite::GetByID(const TCategoryID catID)
{
	if (!Exists(catID))
		return InvalidQCategory;

	QCategory qc(InvalidQCategory);

	if (!m_Base.DoSQL([&catID, &qc, this] (SQLiteStatement s)
	{
		s.Sql("SELECT * FROM Categories WHERE id=@id");
		s.BindInt(1, catID);

		if (!s.FetchRow())
			return false;

		qc = CreateQCategory(s.GetColumnInt(0),
							 s.GetColumnString(1));
							
		return true;
	}))
		return InvalidQCategory;

	return qc;
}

QCategory CategoryDAOSqlite::GetByName(const string& name)
{
	if (!Exists(name))
		return InvalidQCategory;

	QCategory qc(InvalidQCategory);

	if(!m_Base.DoSQL([&name, &qc, this] (SQLiteStatement s)
	{
		s.Sql("SELECT * FROM Categories WHERE name=@name");
		s.BindString(1, name);
		
		if (!s.FetchRow())
			return false;
		qc = CreateQCategory(s.GetColumnInt(0), s.GetColumnString(1));
		return true;
	}))
		return InvalidQCategory;

	return qc;
}

TQCategoryVec CategoryDAOSqlite::GetAll()
{
	TQCategoryVec vec;

	if(!m_Base.DoSQL([&vec, this] (SQLiteStatement s)
	{
		s.Sql("SELECT * FROM Categories");
		
		while (s.FetchRow())
			vec.push_back(CreateQCategory(s.GetColumnInt(0),
										  s.GetColumnString(1)));

		return true;
	}))
		return TQCategoryVec();

	return vec;
}

TQCategoryVec CategoryDAOSqlite::GetAllByDictionary(const TDictionaryID dicID)
{
	TQCategoryVec vec;

	if (!MasterDAO::Dictionaries->Exists(dicID))
		return vec;

	if(!m_Base.DoSQL([&dicID, &vec, this] (SQLiteStatement s)
	{
		s.Sql("SELECT Categories.id, name FROM Categories, DictionaryCategories WHERE Categories.id=DictionaryCategories.category_id AND dictionary_id=@dicID");
		s.BindInt(1, dicID);
		
		while (s.FetchRow())
			vec.push_back(CreateQCategory(s.GetColumnInt(0),
										  s.GetColumnString(1)));

		return true;
	}))
		return TQCategoryVec();

	return vec;
}

TQCategoryVec CategoryDAOSqlite::GetIf(const TQCategoryPredicate& predicate)
{
	TQCategoryVec vec;
	auto categories = GetAll();

	for (auto& category : categories)
		if (predicate(category))
			vec.push_back(category);

	return vec;
}

bool CategoryDAOSqlite::Exists(const TCategoryID id)
{
	return m_Base.DoSQL([&id] (SQLiteStatement s)
	{
		s.Sql("SELECT * FROM Categories WHERE id=@id");
		s.BindInt(1, id);
		return s.FetchRow();
	});
}

bool CategoryDAOSqlite::Exists(const string& name)
{
	return m_Base.DoSQL([&name] (SQLiteStatement s)
	{
		s.Sql("SELECT * FROM Categories WHERE name=@name");
		s.BindString(1, name);
		return s.FetchRow();
	});
}

}
