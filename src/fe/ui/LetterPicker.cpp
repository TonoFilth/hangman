#include "fe/ui/LetterPicker.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
LetterPicker::LetterPicker(const Vector2f& buttonSize, const UI32 cols, const Font& font) :
	m_Rows(0),
	m_Cols(cols),
	m_ButtonSize(buttonSize),
	m_PickerSize(0, 0),
	m_PickerPosition(25, 25),
	m_Font(font),
	m_Alignment(THAlign::CENTER),
	m_LineSpacing(0),
	m_ButtonPadding(0, 0, 0, 0)
{
	if (m_Cols == 0)
		m_Cols = 1;
}

LetterPicker::~LetterPicker()
{
}

// =============================================================================
//	PRIVATE AND PROTECTED METHODS
// =============================================================================
void LetterPicker::ComputePickerSize()
{
	m_PickerSize.x = (m_ButtonPadding.left + m_ButtonPadding.width) * m_Cols +
					  m_Cols * m_ButtonSize.x;
	m_PickerSize.y = (m_ButtonPadding.top + m_ButtonPadding.height +
					  m_LineSpacing) * m_Rows + m_Rows * m_ButtonSize.y;

	// Substract one line spacing because the last
	// button line doesn't have line spacing at bottom
	m_PickerSize.y -= m_LineSpacing;
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
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
void LetterPicker::SetLetters(const String& letters, const sf::Font& font)
{
	F32 lScale = 0.8;

	Vector2f curPos(m_PickerPosition);
	curPos.x += m_ButtonPadding.left;
	curPos.y += m_ButtonPadding.top;

	UI32 curLetter = 0;
	UI32 rowWidth = (m_ButtonPadding.left + m_ButtonPadding.width +
					 m_ButtonSize.x) * m_Cols;

	m_Rows = ceil(letters.getSize() / static_cast<F32>(m_Cols));

	for (UI32 i = 0; i < m_Rows; ++i)
	{
		for (UI32 j = 0; j < m_Cols; ++j)
		{
			LetterButton button(letters[curLetter], font, m_ButtonSize, lScale);
			button.SetPosition(curPos);

			m_Buttons.push_back(button);

			curPos.x += m_ButtonSize.x + m_ButtonPadding.left + m_ButtonPadding.width;

			++curLetter;
			if (curLetter == letters.getSize())
				break;
		}

		if (curLetter == letters.getSize())
			break;

		curPos.x = m_PickerPosition.x + m_ButtonPadding.left;
		curPos.y += m_ButtonPadding.top + m_ButtonPadding.height +
			m_LineSpacing + m_ButtonSize.y;

		// Calculate center
		if (i + 2 == m_Rows)
		{
			UI32 remainingLetters = letters.getSize() - (i + 1) * m_Cols;
			UI32 spaceToFill = remainingLetters * (m_ButtonPadding.left +
				m_ButtonPadding.width + m_ButtonSize.x);
			UI32 emptySpace = rowWidth - spaceToFill;

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

	ComputePickerSize();
}

}