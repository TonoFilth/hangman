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

string database    = "";
string option      = "";
string option_arg1 = "";
string option_arg2 = "";
string option_arg3 = "";
string option_arg4 = "";

TDatabasePtr 	  db;
TWordDAOPtr  	  wordDAO;
TCategoryDAOPtr   categoryDAO;
TDictionaryDAOPtr dictionaryDAO;

bool OpenDatabase()
{
	try
	{
		db = make_shared<SQLiteDatabase>(database, SQLITE_OPEN_READWRITE, nullptr);
	}
	catch (const SQLiteException& ex)
	{
		ex.Show();
		return false;
	}

	wordDAO 	  = make_shared<WordDAOSqlite>(db);
	categoryDAO   = make_shared<CategoryDAOSqlite>(db);
	dictionaryDAO = make_shared<DictionaryDAOSqlite>(db);

	MasterDAO::Words 		= wordDAO;
	MasterDAO::Categories   = categoryDAO;
	MasterDAO::Dictionaries = dictionaryDAO;

	return true;
}

bool OpenDatabaseForCreation()
{
	try
	{
		db = make_shared<SQLiteDatabase>();
		db->Open(database, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);
	}
	catch (const SQLiteException& ex)
	{
		ex.Show();
		return false;
	}

	return true;
}

Dictionary StringToDictionary(const string& str)
{
	auto attrs = StringUtils::ExplodeOmitQuotes(str, " ");

	if (attrs.size() != 4)
		return InvalidDictionary;

	for (auto& s : attrs)
		StringUtils::FindAndReplace(s, "\"", "");

	return Dictionary(attrs[0], attrs[1], attrs[2], attrs[3]);
}

void PrintUnrecognized()
{
	cerr << "Unrecognized option: " << option << endl;
}

void CreateDB()
{
	database += ".sqlite";
	cout << "Creating database " << database << endl;
	if (!OpenDatabaseForCreation())
		return;

	try
	{
		SQLiteStatement s(db.get());
		s.SqlStatement("CREATE TABLE \"Categories\" (\"id\" INTEGER PRIMARY KEY  NOT NULL ,\"name\" TEXT NOT NULL  DEFAULT (null) )");
		s.SqlStatement("CREATE TABLE \"CategoryWords\" (\"category_id\" INTEGER NOT NULL , \"word_id\" INTEGER NOT NULL , PRIMARY KEY (\"category_id\", \"word_id\"))");
		s.SqlStatement("CREATE TABLE \"Dictionaries\" (\"id\" INTEGER PRIMARY KEY  NOT NULL ,\"name\" TEXT NOT NULL  DEFAULT (null) ,\"lang\" TEXT NOT NULL  DEFAULT (null) ,\"character_set\" TEXT NOT NULL  DEFAULT (null) ,\"font_file\" TEXT NOT NULL  DEFAULT (null) )");
		s.SqlStatement("CREATE TABLE \"DictionaryCategories\" (\"dictionary_id\" INTEGER NOT NULL , \"category_id\" INTEGER NOT NULL , PRIMARY KEY (\"dictionary_id\", \"category_id\"))");
		s.SqlStatement("CREATE TABLE \"Words\" (\"id\" INTEGER PRIMARY KEY  NOT NULL ,\"word\" TEXT NOT NULL  DEFAULT (null) ,\"hint\" TEXT DEFAULT (null))");
	}
	catch (const SQLiteException& ex)
	{
		ex.Show();
		return;
	}
}

void AddDictionary()
{
	cout << "Creating dictionary with the following attributes: ";
	cout << option_arg1 << " " << option_arg2 << " " << option_arg3 << " " << option_arg4 << endl;

	cout << (MasterDAO::Dictionaries->Create(option_arg1, option_arg2, option_arg3, option_arg4).IsValid() ? "OK" : "ERROR") << endl;
}

void AddDictionaries()
{
	cout << "Creating dictionaries from file " << option_arg1 << endl;

	UI32 additions = 0;
	list<string> lines;
	Dictionary dictionary;
	TDictionaryVec rejected;
	FileUtils::ReadLines(option_arg1, lines);

	for (auto& line : lines)
	{
		if ((dictionary = StringToDictionary(line)).IsValid())
		{
			if (MasterDAO::Dictionaries->Create(dictionary.GetName(),
											    dictionary.GetLanguage(),
												dictionary.GetCharacterSet(),
												dictionary.GetFont()).IsValid())
				++additions;
			else
				rejected.push_back(dictionary);
		}
		else
		{
			rejected.push_back(dictionary);
		}
	}

	cout << additions << " dictionaries created, " << lines.size() - additions << " rejected" << endl;
	cout << "Rejected:" << endl;

	for (auto& d : rejected)
		cout << " " << d.GetName() << endl;
}

void AddCategory()
{
	cout << "Creating category " << option_arg2 << " in dictionary " << option_arg1 << endl;
}

void AddCategories()
{
	cout << "Creating categories from file " << option_arg1 << endl;
}

void AddWord()
{
	cout << "Creating word " << option_arg2 << " " << option_arg3 << " in category " << option_arg1 << endl;
}

void AddWords()
{
	cout << "Creating words from file " << option_arg1 << endl;
}

bool RemoveDictionary()
{
	cout << "Removing dictionary " << option_arg1 << " | ";

	auto dic = MasterDAO::Dictionaries->GetByName(option_arg1);
	if (!dic.IsValid())
	{
		cerr << "ERROR: Dictionary " << option_arg1 << " doesn't exists" << endl;
		return false;
	}

	cout << (MasterDAO::Dictionaries->Delete(dic.GetID()) ? "OK" : "ERROR") << endl;
	return true;
}

void RemoveDictionaries()
{
	cout << "Removing dictionaries from file " << option_arg1 << endl;

	UI32 deletions = 0;
	list<string> lines;
	FileUtils::ReadLines(option_arg1, lines);

	for (auto& line : lines)
	{
		auto tokens = StringUtils::ExplodeOmitQuotes(line, " ");

		if (tokens.empty())
			continue;

		StringUtils::FindAndReplace(tokens[0], "\"", "");
		option_arg1 = tokens[0];
		if (RemoveDictionary())
			++deletions;
	}

	cout << deletions << " dictionaries removed, " << lines.size() - deletions << " rejected" << endl;
}

void RemoveCategory()
{
	cout << "Removing category " << option_arg1 << endl;
}

void RemoveCategories()
{
	cout << "Removing categories from file " << option_arg1 << endl;
}

void RemoveWord()
{
	cout << "Removing word " << option_arg1 << endl;
}

void RemoveWords()
{
	cout << "Removing words from file " << option_arg1 << endl;
}

void HandleArgs3()
{
	if (option == "-create")
		CreateDB();
	else
		PrintUnrecognized();
}

void HandleArgs4()
{
	if (option == "-add-dictionaries")
		AddDictionaries();
	else if (option == "-add-categories")
		AddCategories();
	else if (option == "-add-words")
		AddWords();
	else if (option == "-remove-dictionary")
		RemoveDictionary();
	else if (option == "-remove-dictionaries")
		RemoveDictionaries();
	else if (option == "-remove-category")
		RemoveCategory();
	else if (option == "-remove-categories")
		RemoveCategories();
	else if (option == "-remove-word")
		RemoveWord();
	else if (option == "-remove-words")
		RemoveWords();
	else
		PrintUnrecognized();
}

void HandleArgs5()
{
	if (option == "-add-word")
		AddWord();
	else if (option == "-add-category")
		AddCategory();
	else
		PrintUnrecognized();
}

void HandleArgs6()
{
	if (option == "-add-word")
		AddWord();
	else
		PrintUnrecognized();
}

void HandleArgs7()
{
	if (option == "-add-dictionary")
		AddDictionary();
	else
		PrintUnrecognized();
}

int main(int argc, char** argv)
{
	if (argc <= 2)
	{
		cerr << "usage: dbutil [database-file] [option] [option-args]" << endl;
		return 1;
	}

	if (argc != 3)
	{
		database = string(argv[1]);
		option   = string(argv[2]);
		if (!OpenDatabase())
			return 1;
	}
	else
	{
		database = string(argv[2]);
		option   = string(argv[1]);
	}
	
	switch (argc)
	{
		case 3 : HandleArgs3(); break;
		case 4 : option_arg1 = string(argv[3]); HandleArgs4(); break;
		case 5 : option_arg1 = string(argv[3]); option_arg2 = string(argv[4]); HandleArgs5(); break;
		case 6 : option_arg1 = string(argv[3]); option_arg2 = string(argv[4]); option_arg3 = string(argv[5]); HandleArgs6(); break;
		case 7 : option_arg1 = string(argv[3]); option_arg2 = string(argv[4]); option_arg3 = string(argv[5]); option_arg4 = string(argv[6]); HandleArgs7(); break;
		default : break;
	}

	try
	{
		db->ReleaseMemory();
		db->Close();
	}
	catch (const SQLiteException& ex)
	{
		ex.Show();
	}

	/*
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
	*/

	return 0;
}