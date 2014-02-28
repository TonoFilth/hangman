#include "fe/db/WordDAOSqlite.h"

using namespace std;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
WordDAOSqlite::WordDAOSqlite(const TDatabasePtr& db) :
	m_Base(db)
{
}

WordDAOSqlite::~WordDAOSqlite()
{
}

// =============================================================================
//	VIRTUAL METHODS
// =============================================================================
QWord WordDAOSqlite::Create(const TCategoryID catID,
						    const string& str,
							const string& hint)
{
	if (!MasterDAO::Categories->Exists(catID))
		return InvalidQWord;

	QWord qw(InvalidQWord);

	if (!m_Base.DoSQL([&catID, &str, &hint, &qw, this] (SQLiteStatement s)
	{
		s.Sql("INSERT INTO Words(word, hint) VALUES(@word, @hint)");
		s.BindString(1, str);
		s.BindString(2, hint);
		s.Execute();

		auto wordID = m_Base.GetDB()->GetLastInsertRowId();
		if (wordID <= 0)
			return false;

		s.FreeQuery();
		s.Sql("INSERT INTO CategoryWords(category_id, word_id) VALUES(@catID, @wordID)");
		s.BindInt(1, catID);
		s.BindInt(2, wordID);
		s.Execute();

		auto relationshipID = m_Base.GetDB()->GetLastInsertRowId();
		if (relationshipID > 0)
		{
			qw = CreateQWord(wordID, str, hint);
			return true;
		}

		return Delete(wordID);
	}))
		return InvalidQWord;

	return qw;
}

bool WordDAOSqlite::Update(const QWord& word)
{
	if (!Exists(word.GetID()))
		return false;

	return m_Base.DoSQL([&word] (SQLiteStatement s)
	{
		s.Sql("UPDATE Words SET word=@word, hint=@hint WHERE id=@id");
		s.BindString(1, word.GetString());
		s.BindString(2, word.GetHint());
		s.BindInt(3, word.GetID());
		s.Execute();

		return true;
	});
}

bool WordDAOSqlite::Delete(const TWordID wordID)
{
	if (!Exists(wordID))
		return false;

	return m_Base.DoSQL([&wordID, this] (SQLiteStatement s)
	{
		// Retrieve category ID associated with this word
		s.Sql("SELECT category_id FROM CategoryWords WHERE word_id=@id");
		s.BindInt(1, wordID);
		
		if (!s.FetchRow())
			return false;

		auto catID = s.GetColumnInt(0);

		// Delete relationship between category and word
		s.FreeQuery();
		s.Sql("DELETE FROM CategoryWords WHERE category_id=@catID AND word_id=@wordID");
		s.BindInt(1, catID);
		s.BindInt(2, wordID);
		s.ExecuteAndFree();

		// Delete word
		s.Sql("DELETE FROM Words WHERE id=@id");
		s.BindInt(1, wordID);
		s.ExecuteAndFree();

		return true;
	});
}

TQWordVec WordDAOSqlite::GetIf(const TQWordPredicate& predicate)
{
	TQWordVec vec;
	auto words = GetAll();

	for (auto& word : words)
		if (predicate(word))
			vec.push_back(word);

	return vec;
}

TQWordVec WordDAOSqlite::GetAll()
{
	TQWordVec vec;

	m_Base.DoSQL([&vec, this] (SQLiteStatement s)
	{
		s.Sql("SELECT * FROM Words");
		while (s.FetchRow())
			vec.push_back(CreateQWord(s.GetColumnInt(0),
									  s.GetColumnString(1),
									  s.GetColumnString(2)));
		return true;
	});

	return vec;
}

TQWordVec WordDAOSqlite::GetAllByCategory(const TCategoryID catID)
{
	TQWordVec vec;

	if (!MasterDAO::Categories->Exists(catID))
		return vec;

	if (!m_Base.DoSQL([&catID, &vec, this] (SQLiteStatement s)
	{
		s.Sql("SELECT Words.id, word, hint FROM Words, CategoryWords WHERE Words.id=CategoryWords.word_id AND category_id=@catID");
		s.BindInt(1, catID);

		while (s.FetchRow())
			vec.push_back(CreateQWord(s.GetColumnInt(0),
									  s.GetColumnString(1),
									  s.GetColumnString(2)));
		return true;
	}))
		return TQWordVec();

	return vec;
}

bool WordDAOSqlite::Exists(const TWordID id)
{
	return m_Base.DoSQL([&id] (SQLiteStatement s)
	{
		s.Sql("SELECT * FROM Words WHERE id=@id");
		s.BindInt(1, id);
		return s.FetchRow();
	});
}

bool WordDAOSqlite::Exists(const string& word)
{
	return m_Base.DoSQL([&word] (SQLiteStatement s)
	{
		s.Sql("SELECT * FROM Words WHERE word=@word");
		s.BindString(1, StringUtils::ToUpper(word));
		return s.FetchRow();
	});
}

}
