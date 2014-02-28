#include "fe/db/DictionaryDAOSqlite.h"

using namespace std;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
DictionaryDAOSqlite::DictionaryDAOSqlite(const TDatabasePtr& db) :
	m_Base(db)
{
}

DictionaryDAOSqlite::~DictionaryDAOSqlite()
{
}

// =============================================================================
//	VIRTUAL METHODS
// =============================================================================
QDictionary DictionaryDAOSqlite::Create(const string& name,
							   			const string& lang,
							   			const string& cset,
							   			const string& font)
{
	QDictionary qd(InvalidQDictionary);

	if (Exists(name))
		return qd;

	m_Base.DoSQL([&name, &lang, &cset, &font, &qd, this] (SQLiteStatement s)
	{
		s.Sql("INSERT INTO Dictionaries(name, lang, character_set, font_file) VALUES(@name, @lang, @cset, @font)");
		s.BindString(1, name);
		s.BindString(2, lang);
		s.BindString(3, cset);
		s.BindString(4, font);
		s.Execute();

		auto id = m_Base.GetDB()->GetLastInsertRowId();
		
		if (id <= 0)
			return false;

		qd = CreateQDictionary(id, name, lang, cset, font);
		return true;
	});

	return qd;
}

bool DictionaryDAOSqlite::Update(const QDictionary& dictionary)
{
	if (!Exists(dictionary.GetID()))
		return false;

	return m_Base.DoSQL([&dictionary] (SQLiteStatement s)
	{
		s.Sql("UPDATE Dictionaries SET name=@name, lang=@lang, character_set=@cset, font_file=@font WHERE id=@id");
		s.BindString(1, dictionary.GetName());
		s.BindString(2, dictionary.GetLanguage());
		s.BindString(3, dictionary.GetCharacterSet());
		s.BindString(4, dictionary.GetFont());
		s.BindInt(5, dictionary.GetID());
		s.Execute();

		return true;
	});
}

bool DictionaryDAOSqlite::Delete(const TDictionaryID dicID)
{
	if (!Exists(dicID))
		return false;

	return m_Base.DoSQL([&dicID, this] (SQLiteStatement s)
	{
		// Delete categories associated with this dictionary
		auto categories = MasterDAO::Categories->GetAllByDictionary(dicID);

		for (auto category : categories)
			if (!MasterDAO::Categories->Delete(category.GetID()))
				cerr << "Category " << category.GetID() << " not deleted" << endl;

		// Delete dictionary
		s.Sql("DELETE FROM Dictionaries WHERE id=@id");
		s.BindInt(1, dicID);
		s.ExecuteAndFree();

		return true;
	});
}

TQDictionaryVec DictionaryDAOSqlite::GetAll()
{
	TQDictionaryVec vec;

	m_Base.DoSQL([&vec, this] (SQLiteStatement s)
	{
		s.Sql("SELECT * FROM Dictionaries");
		while (s.FetchRow())
			vec.push_back(CreateQDictionary(s.GetColumnInt(0),
									  		s.GetColumnString(1),
									  		s.GetColumnString(2),
									  		s.GetColumnString(3),
									  		s.GetColumnString(4)));
		return true;
	});

	return vec;
}

QDictionary DictionaryDAOSqlite::GetByID(const TDictionaryID dicID)
{
	if (!Exists(dicID))
		return InvalidQDictionary;

	QDictionary qd(InvalidQDictionary);

	if (!m_Base.DoSQL([&dicID, &qd, this] (SQLiteStatement s)
	{
		s.Sql("SELECT * FROM Dictionaries WHERE id=@id");
		s.BindInt(1, dicID);

		if (!s.FetchRow())
			return false;

		qd = CreateQDictionary(s.GetColumnInt(0),
							   s.GetColumnString(1),
							   s.GetColumnString(2),
							   s.GetColumnString(3),
							   s.GetColumnString(4));
		return true;
	}))
		return InvalidQDictionary;

	return qd;
}

QDictionary DictionaryDAOSqlite::GetByName(const string& name)
{
	if (!Exists(name))
		return InvalidQDictionary;

	QDictionary qd(InvalidQDictionary);

	if (!m_Base.DoSQL([&name, &qd, this] (SQLiteStatement s)
	{
		s.Sql("SELECT * FROM Dictionaries WHERE name=@name");
		s.BindString(1, name);

		if (!s.FetchRow())
			return false;

		qd = CreateQDictionary(s.GetColumnInt(0),
							   s.GetColumnString(1),
							   s.GetColumnString(2),
							   s.GetColumnString(3),
							   s.GetColumnString(4));
		return true;
	}))
		return InvalidQDictionary;

	return qd;
}

TQDictionaryVec DictionaryDAOSqlite::GetIf(const TQDictionaryPredicate& predicate)
{
	TQDictionaryVec vec;
	auto dictionaries = GetAll();

	for (auto& dictionary : dictionaries)
		if (predicate(dictionary))
			vec.push_back(dictionary);

	return vec;
}

bool DictionaryDAOSqlite::Exists(const TDictionaryID id)
{
	return m_Base.DoSQL([&id] (SQLiteStatement s)
	{
		s.Sql("SELECT * FROM Dictionaries WHERE id=@id");
		s.BindInt(1, id);
		return s.FetchRow();
	});
}

bool DictionaryDAOSqlite::Exists(const string& name)
{
	return m_Base.DoSQL([&name] (SQLiteStatement s)
	{
		s.Sql("SELECT * FROM Dictionaries WHERE name=@name");
		s.BindString(1, name);
		return s.FetchRow();
	});
}

}
