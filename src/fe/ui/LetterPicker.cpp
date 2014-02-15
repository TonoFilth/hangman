#include "fe/ui/LetterPicker.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
LetterPicker::LetterPicker(const UI32 width, const UI32 height, const UI32 cols,
	const TFontPtr& font) :
	m_Rows(0),
	m_Cols(cols),
	m_ButtonSize(0, 0),
	m_PickerSize(width, height),
	m_PickerPosition(0, 0),
	m_Font(font),
	m_Alignment(THAlign::CENTER),
	m_LineSpacing(0),
	m_LetterScale(0.8),
	m_ButtonPadding(0, 0, 0, 0),
	m_LetterCallback(nullptr)
{
}

LetterPicker::~LetterPicker()
{
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
void LetterPicker::HandleInput(const RenderWindow& window)
{
	for (auto& button : m_Buttons)
		if (button.HandleInput(window))
			return;
}

void LetterPicker::Draw(RenderWindow& window) const
{
	for (auto& button : m_Buttons)
		button.Draw(window);

	RectangleShape rect(m_PickerSize);
	rect.setFillColor(Color(0, 0, 0, 0));
	rect.setOutlineColor(Color::Green);
	rect.setOutlineThickness(1);
	rect.setPosition(m_PickerPosition);
	window.draw(rect);
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
void LetterPicker::SetLetters(const String& letters)
{
	Vector2f curPos(m_PickerPosition);
	curPos.x += m_ButtonPadding.left;
	curPos.y += m_ButtonPadding.top;

	UI32 curLetter = 0;
	
	m_Rows = ceil(letters.getSize() / static_cast<F32>(m_Cols));

	// Compute the picker actual drawable size
	m_PickerDrawableSize = Vector2f(
		m_PickerSize.x - (m_ButtonPadding.left + m_ButtonPadding.width) * m_Cols,
		m_PickerSize.y - (m_ButtonPadding.top + m_ButtonPadding.height + m_LineSpacing) * m_Rows);

	// Last row doesn't have line spacing
	m_PickerDrawableSize.y += m_LineSpacing;

	// Define the letter button's size
	m_ButtonSize = Vector2f(m_PickerDrawableSize.x / static_cast<F32>(m_Cols),
							m_PickerDrawableSize.y / static_cast<F32>(m_Rows));

	for (UI32 i = 0; i < m_Rows; ++i)
	{
		for (UI32 j = 0; j < m_Cols; ++j)
		{
			LetterButton button(letters[curLetter], *m_Font, m_ButtonSize, m_LetterScale);
			button.SetPosition(curPos);
			button.SetCallback(m_LetterCallback);

			m_Buttons.push_back(button);

			curPos.x += m_ButtonSize.x + m_ButtonPadding.left + m_ButtonPadding.width;

			++curLetter;
			if (curLetter == letters.getSize())
			//	break;
				return;
		}

		//if (curLetter == letters.getSize())
		//	break;

		curPos.x = m_PickerPosition.x + m_ButtonPadding.left;
		curPos.y += m_ButtonPadding.top + m_ButtonPadding.height +
			m_LineSpacing + m_ButtonSize.y;

		// Set last row's alignment
		if (i + 2 == m_Rows)
		{
			UI32 remainingLetters = letters.getSize() - (i + 1) * m_Cols;
			UI32 spaceToFill = remainingLetters * (m_ButtonPadding.left +
				m_ButtonPadding.width + m_ButtonSize.x);
			UI32 emptySpace = m_PickerSize.x - spaceToFill;

			switch (m_Alignment)
			{
				case THAlign::LEFT   : curPos.x = m_ButtonPadding.left; break;
				case THAlign::CENTER : curPos.x = m_ButtonPadding.left + emptySpace * 0.5; break;
				case THAlign::RIGHT  : curPos.x = m_ButtonPadding.left + emptySpace; break;
				default : cerr << "ERROR! Bad horizontal alignment" << endl; break;
			}

			curPos.x += m_PickerPosition.x;
		}
	}
}

void LetterPicker::SetLetterColor(const Color& color)
{
	for (auto& button : m_Buttons)
		button.SetLetterColor(color);
}

void LetterPicker::SetLetterCallback(const TLetterCallback& callback)
{
	m_LetterCallback = callback;

	for (auto& button : m_Buttons)
		button.SetCallback(callback);
}

void LetterPicker::SetPosition(const Vector2f& position)
{
	m_PickerPosition = position;

	if (m_Buttons.empty())
		return;

	Vector2f diff(position.x - m_Buttons.front().GetPosition().x,
				  position.y - m_Buttons.front().GetPosition().y);

	for (auto& button : m_Buttons)
	{
		auto bPos = button.GetPosition();
		button.SetPosition(Vector2f(bPos.x + diff.x, bPos.y + diff.y));
	}
}

}
