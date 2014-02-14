#include "fe/ui/CharacterButton.h"

using namespace std;
using namespace sf;

namespace fe
{

void CenterTextOrigin(Text& text)
{
	auto bounds = text.getLocalBounds();

	text.setOrigin(bounds.left + bounds.width  * 0.5,
				   bounds.top  + bounds.height * 0.5);
}

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
CharacterButton::CharacterButton(const Font& font, const String& character,
	const Color& color) :
	m_Character(character, font)
{
	auto chBounds = m_Character.getLocalBounds();

	m_Button.setSize(Vector2f(chBounds.width + 10, chBounds.height + 10));
	m_Button.setFillColor(Color::Black);

	CenterTextOrigin(m_Character);
	SetColor(color);
	SetPosition(m_Button.getPosition());
}

CharacterButton::CharacterButton(const CharacterButton& toCopy)
{
	Copy(toCopy);
}

CharacterButton& CharacterButton::operator=(const CharacterButton& toCopy)
{
	if (this == &toCopy)
		return *this;

	Copy(toCopy);

	return *this;
}

CharacterButton::~CharacterButton()
{
}

// =============================================================================
//	PRIVATE AND PROTECTED METHODS
// =============================================================================
void CharacterButton::Copy(const CharacterButton& toCopy)
{
	m_Character = toCopy.m_Character;
	m_Button 	= toCopy.m_Button;
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
void CharacterButton::Draw(RenderWindow& window) const
{
	window.draw(m_Button);
	window.draw(m_Character);
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
FloatRect CharacterButton::GetBounds() const
{
	return m_Button.getLocalBounds();
}

Vector2f CharacterButton::GetPosition() const
{
	return m_Button.getPosition();
}

void CharacterButton::SetPosition(const Vector2f& position)
{
	m_Button.setPosition(position);

	auto bBounds = m_Button.getLocalBounds();
	auto bPos = m_Button.getPosition();

	m_Character.setPosition(bPos.x + bBounds.width * 0.5,
		bPos.y + bBounds.height * 0.5);
}

void CharacterButton::SetCharacter(const String& character)
{
	if (character.getSize() > 1)
		return;

	m_Character.setString(character);
}

void CharacterButton::SetColor(const Color& color)
{
	m_Character.setColor(color);
}

}
