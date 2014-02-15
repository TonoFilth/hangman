#ifndef __LETTER_PICKER_H__
#define __LETTER_PICKER_H__

#include <iostream>
#include <cmath>

#include "fe/ui/LetterButton.h"

namespace fe
{

class LetterPicker
{
private:
	UI32 m_Rows;
	UI32 m_Cols;

	sf::Vector2f m_ButtonSize;
	sf::Vector2f m_PickerSize;
	sf::Vector2f m_PickerPosition;

	sf::Font      m_Font;
	THAlign 	  m_Alignment;
	UI32 	   	  m_LineSpacing;
	sf::FloatRect m_ButtonPadding;

	TLetterCallback   m_LetterCallback;
	TLetterButtonList m_Buttons;

	void ComputePickerSize();

	LetterPicker(const LetterPicker& toCopy);
	LetterPicker& operator=(const LetterPicker& toCopy);

public:
	LetterPicker(const sf::Vector2f& buttonSize, const UI32 cols, const sf::Font& font);
	~LetterPicker();

	void HandleInput(const sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window) const;

	void SetLetters(const sf::String& letters, const sf::Font& font);
	void SetLetterColor(const sf::Color& color);
	void SetLetterCallback(const TLetterCallback& callback);
};

}

#endif
