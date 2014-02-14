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
}

Hangman::~Hangman()
{
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
bool Hangman::BuildFromBodyParts(const TBodyPartVec& bodyParts)
{
	if (!BodyPartChecker::Check(bodyParts))
	{
		cerr << "Malformed body parts" << endl;
		return false;
	}

	m_BodyParts = bodyParts;

	return true;
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
