#include "fe/hangman/Hangman.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
Hangman::Hangman() :
	m_LastShown(0)
{
}

Hangman::~Hangman()
{
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
bool Hangman::ShowNextBodyPart()
{
	if (m_LastShown + 1 > m_Hangman.size())
		return false;

	++m_LastShown;

	return true;
}

void Hangman::HideAllBodyParts()
{
	m_LastShown = 0;
}

void Hangman::Draw(RenderWindow& window) const
{
	for (UI32 i = 0; i < m_LastShown; ++i)
		window.draw(m_Hangman[i]);
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
void Hangman::SetPosition(const Vector2f& position)
{
	if (m_Hangman.empty())
		return;

	Vector2f diff(position.x - m_Hangman[0].getPosition().x,
				  position.y - m_Hangman[0].getPosition().y);

	for (auto& sprite : m_Hangman)
	{
		auto sPos = sprite.getPosition();
		sprite.setPosition(sPos.x + diff.x, sPos.y + diff.y);
	}
}

// =============================================================================
//	DEBUG METHODS
// =============================================================================
void Hangman::PrintDebug(const std::string& spaces) const
{
	cout << spaces << "Hangman" << endl;
	cout << spaces << "  Texture: --" << endl;
}

}
