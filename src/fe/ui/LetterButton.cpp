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
	m_Letter(letter, font),
	m_Callback(nullptr)
{
	m_Button.setSize(buttonSize);
	m_Button.setFillColor(Color::Black);
	m_Button.setPosition(0, 0);
	m_Letter.setColor(Color::White);

	FitLetter(letterScale);
	//TransformableSetOrigin(m_Letter, THAlign::CENTER, TVAlign::CENTER);

	auto bPos(m_Button.getPosition());
	auto lBounds(m_Letter.getLocalBounds());

	//Vector2f letterPos(bPos.x + buttonSize.x  * 0.5,
	//				   bPos.y + buttonSize.y  * 0.5);
	Vector2f letterPos(bPos.x + buttonSize.x * 0.5 - (lBounds.width + lBounds.left) * 0.5,
					   bPos.y + buttonSize.y * 0.5 - (lBounds.height + lBounds.top) * 0.5 - lBounds.top * 0.5);

	m_Letter.setPosition(letterPos);
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
	m_Letter   = toCopy.m_Letter;
	m_Button   = toCopy.m_Button;
	m_Callback = toCopy.m_Callback;
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
bool LetterButton::HandleInput(const RenderWindow& window)
{
	Vector2f mousePos(Mouse::getPosition(window));
	auto lPos(m_Button.getPosition());
	auto lBounds(m_Button.getLocalBounds());

	if (m_Callback != nullptr &&
		mousePos.x >= lPos.x && mousePos.x <= lPos.x + lBounds.width &&
		mousePos.y >= lPos.y && mousePos.y <= lPos.y + lBounds.height)
	{
		m_Callback(this, m_Letter.getString()[0]);
		return true;
	}

	return false;
}

void LetterButton::Draw(RenderWindow& window) const
{
	window.draw(m_Button);
	window.draw(m_Letter);

	// DEBUG RECTANGLES
	/*
	auto lBounds = m_Letter.getLocalBounds();

	auto glyph = m_Letter.getFont()->getGlyph(m_Letter.getString()[0], m_Letter.getCharacterSize(), false);
	RectangleShape sh(
		Vector2f(glyph.bounds.width,
				 lBounds.top));
	sh.setFillColor(Color(0, 0, 0, 0));
	sh.setOutlineColor(Color::Magenta);
	sh.setOutlineThickness(1.0);
	sh.setPosition(m_Letter.getPosition());
	window.draw(sh);

	RectangleShape shape(
		Vector2f(lBounds.width + lBounds.left,
				 lBounds.height + lBounds.top));
	shape.setFillColor(Color(0, 0, 0, 0));
	shape.setOutlineColor(Color::Red);
	shape.setOutlineThickness(1.0);
	shape.setPosition(m_Letter.getPosition());
	window.draw(shape);
	*/
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
wchar_t LetterButton::GetLetter() const
{
	return m_Letter.getString()[0];
}

Vector2f LetterButton::GetPosition() const
{
	return m_Button.getPosition();
}

void LetterButton::SetLetter(const wchar_t letter)
{
	m_Letter.setString(letter);
}

void LetterButton::SetLetterColor(const Color& color)
{
	m_Letter.setColor(color);
}

void LetterButton::SetButtonColor(const Color& color)
{
	m_Button.setFillColor(color);
}

void LetterButton::SetCallback(const TLetterCallback& callback)
{
	m_Callback = callback;
}

void LetterButton::SetPosition(const Vector2f& position)
{
	m_Button.setPosition(position);

	auto bPos(m_Button.getPosition());
	auto lPos(m_Letter.getPosition());
	auto bSize(m_Button.getSize());

	auto lBounds = m_Letter.getLocalBounds();
	//auto glyph = m_Letter.getFont()->getGlyph(m_Letter.getString()[0], m_Letter.getCharacterSize(), false);
	
	/*Vector2f letterPos(bPos.x + bSize.x * 0.5 - (lBounds.width + lBounds.left) * 0.5,
					   bPos.y + bSize.y * 0.5 - (lBounds.height + lBounds.top) * 0.5);*/
	Vector2f letterPos(bPos.x + bSize.x * 0.5 - (lBounds.width + lBounds.left) * 0.5,
					   bPos.y + bSize.y * 0.5 - (lBounds.height + lBounds.top) * 0.5 - lBounds.top * 0.5);
	
	m_Letter.setPosition(letterPos);

	/*cout << (char)m_Letter.getString()[0] <<" l=" << glyph.bounds.left << " t=" << glyph.bounds.top;
	cout << " w=" << glyph.bounds.width << " h=" << glyph.bounds.height;
	cout << " diff-> x=" << glyph.bounds.width - lBounds.width << " y=" << glyph.bounds.height - lBounds.height << endl;*/
}

}
