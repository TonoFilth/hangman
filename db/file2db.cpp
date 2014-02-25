#include <iostream>
#include <fstream>
#include <SFML/System.hpp>

#include "fe/db/WordDAOSqlite.h"
#include "fe/db/CategoryDAOSqlite.h"
#include "fe/db/DictionaryDAOSqlite.h"
#include "fe/utils/FileUtils.h"
#include "fe/utils/StringUtils.h"
#include "utf8cpp/utf8.h"

using namespace std;
using namespace sf;
using namespace Kompex;
using namespace fe;

string Sanitize(const string& str)
{
	string out(str);
	StringUtils::Translate(out, { 
								   "á", "é", "í", "ó", "ú",
								   "à", "è", "ì", "ò", "ù",
								   "ä", "ë", "ï", "ö", "ü",
								   "Á", "É", "Í", "Ó", "Ú",
								   "À", "È", "Ì", "Ò", "Ù",
								   "Ä", "Ë", "Ï", "Ö", "Ü",
								   "ñ" },
								 { 
								   "a", "e", "i", "o", "u",
								   "a", "e", "i", "o", "u",
								   "a", "e", "i", "o", "u",
								   "A", "E", "I", "O", "U",
								   "A", "E", "I", "O", "U",
								   "A", "E", "I", "O", "U",
								   "Ñ" });

	return out;
}

int main(int argc, char** argv)
{
	if (argc < 4)
	{
		cerr << "usage: file2db <database-file> <file> <operation>" << endl;
		return 1;
	}

	TDatabasePtr db = make_shared<SQLiteDatabase>(argv[1], SQLITE_OPEN_READWRITE, nullptr);

	TIDictionaryDAOPtr dictionaryDAO = make_shared<DictionaryDAOSqlite>(db);
	TICategoryDAOPtr   categoryDAO 	 = make_shared<CategoryDAOSqlite>(db);
	TIWordDAOPtr 	   wordDAO 		 = make_shared<WordDAOSqlite>(db);

	DictionaryDAO::SetDAO(dictionaryDAO);
	CategoryDAO::SetDAO(categoryDAO);
	WordDAO::SetDAO(wordDAO);

	UI32 counter = 0;
	list<string> lines;
	String currentCategory("");

	FileUtils::ReadLines(string(argv[2]), lines);

	for (auto& str : lines)
	{
		string transformed(StringUtils::ToUpper(Sanitize(str)));

		if (!StringUtils::IsU8(transformed))
		{
			cerr << "\"" << transformed << "\" is not an UTF-8 valid string" << endl;
			continue;
		}

		cout << "Saving " << str << " -> " << transformed << " | " << (WordDAO::InsertWord(1, Word(transformed, "")) ? "OK" : "ERR") << endl;
		++counter;
	}

	cout << "---" << endl;
	cout << "Done! " << counter << " words saved, ";
	cout << lines.size() - counter << " rejected" << endl;

	try
	{
		db->ReleaseMemory();
		db->Close();
	}
	catch (SQLiteException& ex)
	{
		ex.Show();
		return 1;
	}

	return 0;
}