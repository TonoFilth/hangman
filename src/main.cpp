#include <iostream>
#include "fe/hangman/Hangman.h"
#include "fe/hangman/factory/HangmanFactory.h"
#include "fe/hangman/factory/OrderedBodyBuilder.h"
#include "fe/hangman/factory/StubBodyPartExtractor.h"
#include "fe/words/Word.h"
#include "fe/words/StubWordProvider.h"
#include "fe/ui/LetterButton.h"
#include "fe/ui/LetterPicker.h"

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

	hangman->SetPosition(Vector2f(250, 250));

	IWordProvider* wordProvider = new StubWordProvider();

	Font f;
	f.loadFromFile("assets/fonts/Exo-Black.otf");

	Text t(wordProvider->GetCharacterList(), f);
	t.setColor(Color::Black);

	LetterPicker picker(Vector2f(30, 30), 3, f);
	picker.SetLetters(L"ABCDEFGHIJKLMNÑOPQRSTUVWXYZ", f);

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
				if (!hangman->ShowNextBodyPart())
					hangman->HideAllBodyParts();
				t.setString(wordProvider->GetNextWord().GetWord());
			}
		}

		window.clear(Color::White);
		hangman->Draw(window);
		window.draw(t);
		picker.Draw(window);
		window.display();
	}

	delete wordProvider;
	delete bBuilder;
	delete bpExtractor;

	return 0;
}