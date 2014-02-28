#include <iostream>
#include "fe/hangman/factory/HangmanFactory.h"
#include "fe/hangman/factory/OrderedBodyBuilder.h"
#include "fe/hangman/factory/JsonBodyPartExtractor.h"
#include "fe/ui/LetterPicker.h"
#include "fe/ui/WordViewer.h"
#include "fe/words/Dictionary.h"

//#include "fe/db/WordDAOSqlite.h"
//#include "fe/db/CategoryDAOSqlite.h"
//#include "fe/db/DictionaryDAOSqlite.h"
#include "Kompex/KompexSQLiteDatabase.h"
#include "Kompex/KompexSQLiteStatement.h"
#include "Kompex/KompexSQLiteException.h"

#include "fe/db/WordDAOSqlite.h"
#include "fe/db/CategoryDAOSqlite.h"
#include "fe/db/DictionaryDAOSqlite.h"

using namespace std;
using namespace sf;
using namespace Kompex;
using namespace fe;

int main(int argc, char** argv)
{
	TDatabasePtr db = make_shared<SQLiteDatabase>("hangman.sqlite", SQLITE_OPEN_READWRITE, nullptr);

	TWordDAOPtr 	  wordDAO 		= make_shared<WordDAOSqlite>(db);
	TCategoryDAOPtr   categoryDAO   = make_shared<CategoryDAOSqlite>(db);
	TDictionaryDAOPtr dictionaryDAO = make_shared<DictionaryDAOSqlite>(db);

	MasterDAO::Words 		= wordDAO;
	MasterDAO::Categories   = categoryDAO;
	MasterDAO::Dictionaries = dictionaryDAO;

	auto dictionary = MasterDAO::Dictionaries->GetByID(1);

	if (!dictionary.IsValid())
	{
		cerr << "Invalid dictionary" << endl;
		return 1;
	}

	TBodyBuilderPtr       bBuilder    = make_shared<OrderedBodyBuilder>();
	TBodyPartExtractorPtr bpExtractor = make_shared<JsonBodyPartExtractor>("assets/json/default-body.json");

	THangmanShPtr hangman;
	HangmanFactory factory(bpExtractor, bBuilder);

	if ((hangman = factory.Create()) == nullptr)
	{
		cerr << "Can't build hangman. Terminating ..." << endl;
		return 1;
	}

	hangman->SetPosition(Vector2f(250, 100));

	Texture guidesTexture;
	guidesTexture.loadFromFile("assets/images/guides.png");
	Sprite guides(guidesTexture);
	guides.setPosition(0, 0);

	TTexturePtr txUnderline = make_shared<Texture>();
	txUnderline->loadFromFile("assets/images/underline.png");

	bool nextWord = false;

	TFontPtr dictionaryFont = make_shared<Font>();
	if (!dictionaryFont->loadFromFile(dictionary.GetFont()))
	{
		cerr << "Can't load dictionary's font: " << dictionary.GetFont() << endl;
		return 1;
	}

	WordViewer wViewer(500, 50, dictionaryFont, txUnderline);
	wViewer.SetWord(Word(dictionary.GetRandomWord()));

	LetterPicker picker(500, 100, 10, dictionaryFont);
	picker.SetPosition(Vector2f(0, 400));
	picker.SetLetters(dictionary.GetCharacterSet());
	picker.SetLetterCallback([&wViewer, &hangman](LetterButton* b, const string& c)
	{
		// ******* IF PLAYER CLICKS TWO TIMES THE SAME LETTER
		// ******* COUNTS AS A NEW LETTER CLICK - FIX IT!
		if (!wViewer.TryLetter(c))
		{
			hangman->ShowNextBodyPart();
			b->SetLetterColor(Color::Red);

			if (hangman->IsFullyVisible())
				wViewer.RevealWord();
		}
		else
		{
			b->SetLetterColor(Color::Green);
		}
	});

	RenderWindow window(VideoMode(500, 500), "Hangman");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed)
			{
				picker.HandleInput(window);
				
				if (nextWord)
				{
					wViewer.SetWord(dictionary.GetRandomWord());
					picker.SetLetterColor(Color::White);
					hangman->HideAllBodyParts();
					nextWord = false;
				}

				if (wViewer.IsWordVisible() || hangman->IsFullyVisible())
					nextWord = true;
			}
		}

		window.clear(Color::White);
		hangman->Draw(window);
		picker.Draw(window);
		wViewer.Draw(window);
		window.draw(guides);
		window.display();
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

	return 0;
}