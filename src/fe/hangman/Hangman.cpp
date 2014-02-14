#include "fe/hangman/Hangman.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
Hangman::Hangman(const string& textureFile)
{
	if (!m_Texture.loadFromFile(textureFile))
	{
		cerr << "Can't load texture: " << textureFile << endl;
		throw;
	}

	m_Texture.setSmooth(true);
}

Hangman::~Hangman()
{
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
bool Hangman::BuildFromBodyParts(const TBodyPartVec& bodyParts, const Vector2f& position)
{
	if (!BodyPartChecker::Check(bodyParts))
	{
		cerr << "Malformed body parts" << endl;
		return false;
	}

	m_BodyParts = bodyParts;
	BodyBuilder::Build(bodyParts, m_Texture, position, m_Hangman);

	return true;
}

void Hangman::Draw(RenderWindow& window) const
{
	for (auto& sprite : m_Hangman)
		window.draw(sprite);
}

// =============================================================================
//	DEBUG METHODS
// =============================================================================
void Hangman::PrintDebug(const std::string& spaces) const
{
	cout << spaces << "Hangman" << endl;
	cout << spaces << "  Texture: --" << endl;

	for (auto& bodyPart : m_BodyParts)
		bodyPart.PrintDebug(spaces + "  ");
}

}
