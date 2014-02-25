#include "fe/ui/LetterButton.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
LetterButton::LetterButton(const string& letter, const TFontPtr& font,
						   const Vector2f& buttonSize, F32 letterScale) :
	m_Label(StringUtils::U8toU32(letter).data(), *font),
	m_Font(font),
	m_Callback(nullptr)
{
	m_Background.setSize(buttonSize);
	m_Background.setFillColor(Color::Black);
	m_Background.setPosition(0, 0);
	m_Label.setColor(Color::White);

	FitLabel(letterScale);
	
	auto bPos(m_Background.getPosition());
	auto lBounds(m_Label.getLocalBounds());

	Vector2f letterPos(bPos.x + buttonSize.x * 0.5 - (lBounds.width + lBounds.left) * 0.5,
					   bPos.y + buttonSize.y * 0.5 - (lBounds.height + lBounds.top) * 0.5 - lBounds.top * 0.5);

	m_Label.setPosition(letterPos);
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
	m_Label   	 = toCopy.m_Label;
	m_Font		 = toCopy.m_Font;
	m_Background = toCopy.m_Background;
	m_Callback 	 = toCopy.m_Callback;
}

void LetterButton::FitLabel(const F32 letterScale)
{
	auto bSize 	 = m_Background.getSize();
	auto lBounds = m_Label.getGlobalBounds();
	auto chSize  = m_Label.getCharacterSize();

	auto curHeight 	   = lBounds.height + lBounds.top;
	auto desiredHeight = bSize.y * letterScale;

	// Increase character size
	while (curHeight < desiredHeight)
	{
		m_Label.setCharacterSize(++chSize);
		lBounds = m_Label.getGlobalBounds();
		curHeight = lBounds.height + lBounds.top;
	}

	m_Label.setCharacterSize(--chSize);
	
	// Decrease character size
	while (curHeight > desiredHeight)
	{
		m_Label.setCharacterSize(--chSize);
		lBounds = m_Label.getGlobalBounds();
		curHeight = lBounds.height + lBounds.top;
	}

	m_Label.setCharacterSize(--chSize);
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
bool LetterButton::HandleInput(const RenderWindow& window)
{
	Vector2f mousePos(Mouse::getPosition(window));
	auto lPos(m_Background.getPosition());
	auto lBounds(m_Background.getLocalBounds());

	if (m_Callback != nullptr &&
		mousePos.x >= lPos.x && mousePos.x <= lPos.x + lBounds.width &&
		mousePos.y >= lPos.y && mousePos.y <= lPos.y + lBounds.height)
	{
		m_Callback(this, m_Label.getString());
		return true;
	}

	return false;
}

void LetterButton::Draw(RenderWindow& window) const
{
	window.draw(m_Background);
	window.draw(m_Label);

	// DEBUG RECTANGLES
	/*
	auto lBounds = m_Label.getLocalBounds();

	auto glyph = m_Label.getFont()->getGlyph(m_Label.getString()[0], m_Label.getCharacterSize(), false);
	RectangleShape sh(
		Vector2f(glyph.bounds.width,
				 lBounds.top));
	sh.setFillColor(Color(0, 0, 0, 0));
	sh.setOutlineColor(Color::Magenta);
	sh.setOutlineThickness(1.0);
	sh.setPosition(m_Label.getPosition());
	window.draw(sh);

	RectangleShape shape(
		Vector2f(lBounds.width + lBounds.left,
				 lBounds.height + lBounds.top));
	shape.setFillColor(Color(0, 0, 0, 0));
	shape.setOutlineColor(Color::Red);
	shape.setOutlineThickness(1.0);
	shape.setPosition(m_Label.getPosition());
	window.draw(shape);
	*/
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
string LetterButton::GetLetter() const
{
	return StringUtils::SFMLtoU8(m_Label.getString());
}

Vector2f LetterButton::GetPosition() const
{
	return m_Background.getPosition();
}

void LetterButton::SetLetter(const string& letter)
{
	m_Label.setString(StringUtils::U8toSFML(letter));
}

void LetterButton::SetLetterColor(const Color& color)
{
	m_Label.setColor(color);
}

void LetterButton::SetButtonColor(const Color& color)
{
	m_Background.setFillColor(color);
}

void LetterButton::SetCallback(const TLetterCallback& callback)
{
	m_Callback = callback;
}

void LetterButton::SetPosition(const Vector2f& position)
{
	m_Background.setPosition(position);

	auto bPos(m_Background.getPosition());
	auto lPos(m_Label.getPosition());
	auto bSize(m_Background.getSize());

	auto lBounds = m_Label.getLocalBounds();
	//auto glyph = m_Label.getFont()->getGlyph(m_Label.getString()[0], m_Label.getCharacterSize(), false);
	
	/*Vector2f letterPos(bPos.x + bSize.x * 0.5 - (lBounds.width + lBounds.left) * 0.5,
					   bPos.y + bSize.y * 0.5 - (lBounds.height + lBounds.top) * 0.5);*/
	Vector2f letterPos(bPos.x + bSize.x * 0.5 - (lBounds.width + lBounds.left) * 0.5,
					   bPos.y + bSize.y * 0.5 - (lBounds.height + lBounds.top) * 0.5 - lBounds.top * 0.5);
	
	m_Label.setPosition(letterPos);

	/*cout << (char)m_Label.getString()[0] <<" l=" << glyph.bounds.left << " t=" << glyph.bounds.top;
	cout << " w=" << glyph.bounds.width << " h=" << glyph.bounds.height;
	cout << " diff-> x=" << glyph.bounds.width - lBounds.width << " y=" << glyph.bounds.height - lBounds.height << endl;*/
}

}
