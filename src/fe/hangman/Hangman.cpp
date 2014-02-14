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
}

Hangman::~Hangman()
{
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
void Hangman::BuildFromBodyParts(const TBodyPartVec& bodyParts)
{
	m_BodyParts = bodyParts;
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
