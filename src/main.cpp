#include <iostream>
#include "fe/hangman/Hangman.h"
#include "fe/hangman/factory/HangmanFactory.h"
#include "fe/hangman/factory/OrderedBodyBuilder.h"
#include "fe/hangman/factory/StubBodyPartExtractor.h"
#include "fe/words/Word.h"
#include "fe/words/StubWordProvider.h"
#include "fe/ui/CharacterButton.h"
#include "fe/ui/CharacterPicker.h"

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
	wordProvider->SetCurrentCategory("empty");
	wordProvider->SetCurrentCategory("exists");
	wordProvider->SetCurrentCategory("default");

	Font f;
	f.loadFromFile("assets/fonts/Exo-Black.otf");

	Text t(wordProvider->GetCharacterList(), f);
	t.setColor(Color::Black);

	CharacterButton cbutton(f, L"A", Color::White);
	cbutton.SetPosition(Vector2f(250, 250));
	cbutton.SetCharacter(L"Ñ");
	cbutton.SetColor(Color::Red);

	CharacterPicker cbPicker(f);
	cbPicker.SetCharacterList(wordProvider->GetCharacterList());

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
		//cbutton.Draw(window);
		cbPicker.Draw(window);
		window.display();
	}

	delete wordProvider;
	delete bBuilder;
	delete bpExtractor;

	return 0;
}