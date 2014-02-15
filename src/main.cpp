#include <iostream>
#include "fe/hangman/Hangman.h"
#include "fe/hangman/factory/HangmanFactory.h"
#include "fe/hangman/factory/OrderedBodyBuilder.h"
#include "fe/hangman/factory/StubBodyPartExtractor.h"
#include "fe/words/Word.h"
#include "fe/words/StubWordProvider.h"
#include "fe/ui/LetterButton.h"
#include "fe/ui/LetterPicker.h"
#include "fe/ui/WordViewer.h"

using namespace std;
using namespace sf;
using namespace fe;

int main(int argc, char** argv)
{
	IBodyBuilder* bBuilder 			= new OrderedBodyBuilder();
	IBodyPartExtractor* bpExtractor = new StubBodyPartExtractor();

	THangmanShPtr hangman;
	HangmanFactory factory(bpExtractor, bBuilder);

	if ((hangman = factory.CreateFromFile("myfile.txt")) == nullptr)
	{
		cerr << "Exiting ..." << endl;
		return 1;
	}

	hangman->SetPosition(Vector2f(250, 100));

	IWordProvider* wordProvider = new StubWordProvider();

	//Font f;
	//f.loadFromFile("assets/fonts/Exo-Black.otf");
	//f.loadFromFile("assets/fonts/osaka.unicode.ttf");

	//Text t(wordProvider->GetCharacterList(), f);
	//t.setColor(Color::Black);

	TTexturePtr txPtr = make_shared<Texture>();
	TFontPtr fPtr = make_shared<Font>();

	txPtr->loadFromFile("assets/images/underline.png");
	fPtr->loadFromFile("assets/fonts/osaka.unicode.ttf");

	bool nextWord = false;

	WordViewer wViewer(500, 50, fPtr, txPtr);
	wViewer.SetWord(Word("ABABAB"));

	//LetterPicker picker(Vector2f(40, 40), 6, f);
	LetterPicker picker(500, 100, 10, fPtr);
	picker.SetPosition(Vector2f(0, 400));
	//picker.SetLetters(L"んわらやまはなたさかあっゐりみひにちしきい゛るゆむふぬつすくうーゑれめへねてせけえヶをろよもほのとそこお");
	picker.SetLetters(L"ABCDEFGHIJKLMNÑOPQRSTUVWXYZ");
	picker.SetLetterCallback([&wViewer, &hangman](LetterButton* b, const wchar_t c)
	{
		//cout << String(c).toAnsiString() << endl;
		//b->SetLetter(L'-');

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

	for (auto& category : wordProvider->GetAvaliableCategories())
		cout << category.toAnsiString() << endl;

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
				
				//wViewer.TryLetter(L'A');
				if (nextWord)
				{
					wViewer.SetWord(wordProvider->GetNextWord().GetWord());
					picker.SetLetterColor(Color::White);
					hangman->HideAllBodyParts();
					nextWord = false;
				}

				if (wViewer.IsWordVisible() || hangman->IsFullyVisible())
					nextWord = true;

				//if (!hangman->ShowNextBodyPart())
				//	hangman->HideAllBodyParts();
				//t.setString(wordProvider->GetNextWord().GetWord());
			}
		}

		window.clear(Color::White);
		hangman->Draw(window);
		//window.draw(t);
		picker.Draw(window);
		wViewer.Draw(window);
		window.display();
	}

	delete wordProvider;
	delete bBuilder;
	delete bpExtractor;

	return 0;
}