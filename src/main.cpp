#include <iostream>
#include "fe/hangman/Hangman.h"
#include "fe/hangman/factory/HangmanFactory.h"
#include "fe/hangman/factory/OrderedBodyBuilder.h"
#include "fe/hangman/factory/StubBodyPartExtractor.h"

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

	RenderWindow window(VideoMode(500, 500), "Hangman");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed)
				if (!hangman->ShowNextBodyPart())
					hangman->HideAllBodyParts();
		}

		window.clear(Color::White);
		hangman->Draw(window);
		window.display();
	}

	delete bBuilder;
	delete bpExtractor;

	return 0;
}