#ifndef __LETTER_BUTTON_H__
#define __LETTER_BUTTON_H__

#include <string>
#include <list>
#include <functional>
#include <SFML/Graphics.hpp>

#include "fe/types/BasicTypes.h"
#include "fe/types/Alignment.h"
#include "fe/utils/TransformableUtils.h"

namespace fe
{

class LetterButton;

typedef std::list<LetterButton> TLetterButtonList;
typedef std::function<void(LetterButton* sender, const wchar_t)> TLetterCallback;

class LetterButton
{
private:
	sf::Text 		   m_Letter;
	sf::RectangleShape m_Button;
	TLetterCallback    m_Callback;

	void Copy(const LetterButton& toCopy);
	void FitLetter(const F32 letterScale);

public:
	LetterButton(const wchar_t letter, const sf::Font& font,
		const sf::Vector2f& buttonSize, F32 letterScale = 0.8);
	LetterButton(const LetterButton& toCopy);
	LetterButton& operator=(const LetterButton& toCopy);
	~LetterButton();

	bool HandleInput(const sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window) const;

	wchar_t GetLetter() const;
	sf::Vector2f GetPosition() const;

	void SetLetter(const wchar_t letter);
	void SetLetterColor(const sf::Color& color);
	void SetButtonColor(const sf::Color& color);
	void SetCallback(const TLetterCallback& callback);
	void SetPosition(const sf::Vector2f& position);
};

}

#endif
