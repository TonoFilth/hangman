#include "fe/ui/CharacterPicker.h"

using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
CharacterPicker::CharacterPicker(const Font& font) :
	m_Font(font)
{
}

CharacterPicker::~CharacterPicker()
{
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
void CharacterPicker::Draw(sf::RenderWindow& window) const
{
	for (auto& button : m_ButtonList)
		button.Draw(window);
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
void CharacterPicker::SetCharacterList(const sf::String& characterList)
{
	if (characterList == "")
		return;

	UI32 curX = 0, curY = 0;

	for (UI32 i = 0; i < characterList.getSize(); ++i)
	{
		CharacterButton cb(m_Font, characterList[i], Color::White);
		cb.SetPosition(Vector2f(curX, curY));
		m_ButtonList.push_back(cb);
		curX += 30;
	}
}

}
