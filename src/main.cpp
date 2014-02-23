#include <iostream>
#include "fe/hangman/Hangman.h"
#include "fe/hangman/factory/HangmanFactory.h"
#include "fe/hangman/factory/OrderedBodyBuilder.h"
#include "fe/hangman/factory/StubBodyPartExtractor.h"
#include "fe/hangman/factory/JsonBodyPartExtractor.h"
#include "fe/words/Word.h"
#include "fe/ui/LetterButton.h"
#include "fe/ui/LetterPicker.h"
#include "fe/ui/WordViewer.h"
#include "fe/types/UITypes.h"
#include "fe/words/Dictionary.h"
#include "fe/words/RandomDictionary.h"

using namespace std;
using namespace sf;
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
	TFontPtr exoFont = make_shared<Font>(), osakaFont = make_shared<Font>();

	txUnderline->loadFromFile("assets/images/underline.png");
	exoFont->loadFromFile("assets/fonts/Exo-Black.otf");
	osakaFont->loadFromFile("assets/fonts/osaka.unicode.ttf");

	TDictionaryPtr dictionary = make_shared<RandomDictionary>(L"ABCDEFG", "assets/fonts/Exo-Black.otf");
	dictionary->AddCategory("animals");
	dictionary->AddWord(Word(L"DOG"), "animals");
	dictionary->AddWord(Word(L"CAT"), "animals");

	bool nextWord = false;

	WordViewer wViewer(500, 50, exoFont, txUnderline);
	wViewer.SetWord(Word("ABABAB"));

	LetterPicker picker(500, 100, 10, exoFont);
	picker.SetPosition(Vector2f(0, 400));
	//picker.SetLetters(L"んわらやまはなたさかあっゐりみひにちしきい゛るゆむふぬつすくうーゑれめへねてせけえヶをろよもほのとそこお");
	picker.SetLetters(L"ABCDEFGHIJKLMNÑOPQRSTUVWXYZ");
	picker.SetLetterCallback([&wViewer, &hangman](LetterButton* b, const wchar_t c)
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
					wViewer.SetWord(dictionary->GetWord("animals").GetWord());
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

	return 0;
}