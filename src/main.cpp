#include <iostream>
#include "fe/hangman/factory/HangmanFactory.h"
#include "fe/hangman/factory/OrderedBodyBuilder.h"
#include "fe/hangman/factory/JsonBodyPartExtractor.h"
#include "fe/ui/LetterPicker.h"
#include "fe/ui/WordViewer.h"
#include "fe/words/Dictionary.h"

#include "fe/db/WordDAOSqlite.h"
#include "fe/db/CategoryDAOSqlite.h"
#include "fe/db/DictionaryDAOSqlite.h"

using namespace std;
using namespace sf;
using namespace Kompex;
using namespace fe;

int main(int argc, char** argv)
{
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

	TFontPtr exoFont    = make_shared<Font>(),
			 osakaFont  = make_shared<Font>(),
			 monacoFont = make_shared<Font>();

	exoFont->loadFromFile("assets/fonts/Exo-Black.otf");
	osakaFont->loadFromFile("assets/fonts/osaka.unicode.ttf");
	monacoFont->loadFromFile("assets/fonts/Monaco.ttf");

	TDatabasePtr database = make_shared<SQLiteDatabase>("hangman.sqlite", SQLITE_OPEN_READWRITE, nullptr);

	TIDictionaryDAOPtr dictionaryDAO = make_shared<DictionaryDAOSqlite>(database);
	TICategoryDAOPtr   categoryDAO 	 = make_shared<CategoryDAOSqlite>(database);
	TIWordDAOPtr 	   wordDAO 		 = make_shared<WordDAOSqlite>(database);

	DictionaryDAO::SetDAO(dictionaryDAO);
	CategoryDAO::SetDAO(categoryDAO);
	WordDAO::SetDAO(wordDAO);

	//cout << DictionaryDAO::InsertDictionary("English dictionary", "en-EN", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "assets/fonts/Exo-Black.otf") << endl;
	//cout << DictionaryDAO::InsertDictionary("Diccionario español", "es-ES", "ABCDEFGHIJKLMNÑOPQRSTUVWXYZ", "assets/fonts/Monaco.ttf") << endl;
	//cout << DictionaryDAO::InsertDictionary("国語辞典", "jp-JP", "んわらやまはなたさかあっゐりみひにちしきい゛るゆむふぬつすくうーゑれめへねてせけえヶをろよもほのとそこお", "assets/fonts/osaka.unicode.ttf") << endl;
	//cout << DictionaryDAO::GetAllDictionaries().size() << endl;
	//cout << CategoryDAO::InsertCategory(1, "English category 1") << endl;
	//cout << CategoryDAO::InsertCategory(1, "Categoría española 1") << endl;
	//cout << CategoryDAO::InsertCategory(1, "日本カテゴリ1") << endl;
	//cout << CategoryDAO::GetCategoryByID(1).name.toAnsiString() << endl;
	//cout << WordDAO::InsertWord(1, Word("MyWord", "MyHint")) << endl;

	//TDictionaryPtr dictionary = DictionaryDAO::GetDictionaryByID(1);

	auto dictionaries = DictionaryDAO::GetAllDictionaries();
	for (auto& dictionary : dictionaries)
		dictionary->PrintDebug();
	cout << "**************************" << endl;

	auto categories = CategoryDAO::GetCategoriesByDictionaryID(1);
	for (auto& category : categories)
		category.PrintDebug();
	cout << "**************************" << endl;

	auto words = WordDAO::GetWordsByCategoryID(1);
	for (auto& word : words)
		word.PrintDebug();
	cout << "**************************" << endl;

	return 0;
/*
	bool nextWord = false;

	WordViewer wViewer(500, 50, dictionary->GetFont(), txUnderline);
	wViewer.SetWord(Word(dictionary->GetWord()));

	LetterPicker picker(500, 100, 10, dictionary->GetFont());
	picker.SetPosition(Vector2f(0, 400));
	picker.SetLetters(dictionary->GetCharacterSet());
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
					wViewer.SetWord(dictionary->GetWord(1).GetWord());
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
		database->ReleaseMemory();
		database->Close();
	}
	catch (SQLiteException& ex)
	{
		ex.Show();
		return 1;
	}
*/
	return 0;
}