#ifndef __LETTER_BUTTON_H__
#define __LETTER_BUTTON_H__

#include <iostream>
#include <string>
#include <list>
#include <functional>
#include <SFML/Graphics.hpp>

#include "fe/types/UITypes.h"
#include "fe/utils/StringUtils.h"

namespace fe
{

class LetterButton;

typedef std::list<LetterButton> 							   TLetterButtonList;
typedef std::function<void(LetterButton*, const std::string&)> TLetterCallback;

class LetterButton
{
private:
	sf::Text 		   m_Label;
	TFontPtr		   m_Font;
	sf::RectangleShape m_Background;
	TLetterCallback    m_Callback;

	void Copy(const LetterButton& toCopy);
	void FitLabel(F32 lineHeight);

public:
	LetterButton(const std::string& letter, const TFontPtr& font,
		const sf::Vector2f& buttonSize, F32 letterScale = 0.8);
	LetterButton(const LetterButton& toCopy);
	LetterButton& operator=(const LetterButton& toCopy);
	~LetterButton();

	bool HandleInput(const sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window) const;

	std::string GetLetter() const;
	sf::Vector2f GetPosition() const;

	void SetLetter(const std::string& letter);
	void SetLetterColor(const sf::Color& color);
	void SetButtonColor(const sf::Color& color);
	void SetCallback(const TLetterCallback& callback);
	void SetPosition(const sf::Vector2f& position);
};

}

#endif
