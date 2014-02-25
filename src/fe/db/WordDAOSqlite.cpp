#include "fe/db/WordDAOSqlite.h"

using namespace std;
using namespace sf;
using namespace Kompex;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
WordDAOSqlite::WordDAOSqlite(const TDatabasePtr& database) :
	m_Database(database)
{
}

WordDAOSqlite::~WordDAOSqlite()
{
}

// =============================================================================
//	VIRTUAL METHODS
// =============================================================================
bool WordDAOSqlite::InsertWord(const TCategoryID categoryID, const Word& word)
{
	if (!CategoryDAO::Exists(categoryID))
	{
		cerr << "Category with id " << categoryID << " doesn't exists" << endl;
		return false;
	}

	SQLiteStatement s(m_Database.get());

	try
	{
		s.Sql("INSERT INTO Words(word, hint) VALUES(@word, @hint)");
		s.BindString(1, word.GetWord());

		if (word.GetHint() != "")
			s.BindString(2, word.GetHint());
		else
			s.BindNull(2);

		s.FetchRow();
		auto wordID = m_Database->GetLastInsertRowId();
		s.FreeQuery();

		s.Sql("INSERT INTO CategoryWords(category_id, word_id) VALUES(@cid, @wid)");
		s.BindInt(1, categoryID);
		s.BindInt(2, wordID);
		s.FetchRow();
		s.FreeQuery();

		return true;
	}
	catch (SQLiteException& ex)
	{
		ex.Show();
		s.FreeQuery();
		return false;
	}

	s.FreeQuery();

	return false;
}

TWordVec WordDAOSqlite::GetWordsByCategoryID(const TCategoryID categoryID)
{
	if (!CategoryDAO::Exists(categoryID))
	{
		cerr << "Category with id " << categoryID << " doesn't exists" << endl;
		return TWordVec();
	}

	TWordVec words;
	SQLiteStatement s(m_Database.get());

	try
	{
		s.Sql("SELECT word, hint FROM Words, CategoryWords WHERE category_id=@id AND Words.id=CategoryWords.word_id");
		s.BindInt(1, categoryID);

		while (s.FetchRow())
		{
			if (s.GetColumnString(1) == "")
				words.push_back(Word(s.GetColumnString(0), ""));
			else
				words.push_back(Word(s.GetColumnString(0), s.GetColumnString(1)));
		}
	}
	catch (SQLiteException& ex)
	{
		ex.Show();
		s.FreeQuery();
		return TWordVec();
	}

	s.FreeQuery();

	return words;
}

}
