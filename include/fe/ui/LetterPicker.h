#ifndef __LETTER_PICKER_H__
#define __LETTER_PICKER_H__

#include <iostream>
#include <cmath>

#include "fe/ui/LetterButton.h"
#include "fe/types/PointerTypes.h"

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

	TFontPtr	  m_Font;
	THAlign 	  m_Alignment;
	UI32 	   	  m_LineSpacing;
	F32			  m_LetterScale;
	sf::FloatRect m_ButtonPadding;

	TLetterCallback   m_LetterCallback;
	TLetterButtonList m_Buttons;

	void ComputePickerSize();

	LetterPicker(const LetterPicker& toCopy);
	LetterPicker& operator=(const LetterPicker& toCopy);

public:
	LetterPicker(const UI32 width, const UI32 height, const UI32 cols, const TFontPtr& font);
	~LetterPicker();

	void HandleInput(const sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window) const;

	void SetLetters(const sf::String& letters);
	void SetLetterColor(const sf::Color& color);
	void SetLetterCallback(const TLetterCallback& callback);
	void SetPosition(const sf::Vector2f& position);
};

}

#endif
