#include "fe/ui/LetterButton.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
LetterButton::LetterButton(const wchar_t letter, const Font& font,
	const Vector2f& buttonSize, F32 letterScale) :
	m_Letter(letter, font)
{
	m_Button.setSize(buttonSize);
	m_Button.setFillColor(Color::Black);
	m_Button.setPosition(250, 250);
	m_Letter.setColor(Color::Red);
	
	FitLetter(letterScale);
	TransformableSetOrigin(m_Letter, THAlign::CENTER, TVAlign::CENTER);

	auto bPos(m_Button.getPosition());
	m_Letter.setPosition(bPos.x + buttonSize.x  * 0.5,
						 bPos.y + buttonSize.y  * 0.5);
}

LetterButton::LetterButton(const LetterButton& toCopy)
{
	Copy(toCopy);
}

LetterButton& LetterButton::operator=(const LetterButton& toCopy)
{
	if (this == &toCopy)
		return *this;

	Copy(toCopy);

	return *this;
}

LetterButton::~LetterButton()
{
}

// =============================================================================
//	PRIVATE AND PROTECTED METHODS
// =============================================================================
void LetterButton::Copy(const LetterButton& toCopy)
{
	m_Letter = toCopy.m_Letter;
	m_Button = toCopy.m_Button;
}

void LetterButton::FitLetter(const F32 letterScale)
{
	auto bSize 	 = m_Button.getSize();
	auto lBounds = m_Letter.getGlobalBounds();
	auto chSize  = m_Letter.getCharacterSize();

	auto curHeight 	   = lBounds.height + lBounds.top;
	auto desiredHeight = bSize.y * letterScale;

	// Increase character size
	while (curHeight < desiredHeight)
	{
		m_Letter.setCharacterSize(++chSize);
		lBounds = m_Letter.getGlobalBounds();
		curHeight = lBounds.height + lBounds.top;
	}

	m_Letter.setCharacterSize(--chSize);
	
	// Decrease character size
	while (curHeight > desiredHeight)
	{
		m_Letter.setCharacterSize(--chSize);
		lBounds = m_Letter.getGlobalBounds();
		curHeight = lBounds.height + lBounds.top;
	}

	m_Letter.setCharacterSize(--chSize);
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
void LetterButton::Draw(RenderWindow& window) const
{
	window.draw(m_Button);
	window.draw(m_Letter);
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
void LetterButton::SetPosition(const Vector2f& position)
{
	m_Button.setPosition(position);

	auto bPos(m_Button.getPosition());
	auto bSize(m_Button.getSize());
	m_Letter.setPosition(bPos.x + bSize.x  * 0.5,
						 bPos.y + bSize.y  * 0.5);
}

}
