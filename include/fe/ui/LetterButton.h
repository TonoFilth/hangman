#ifndef __LETTER_BUTTON_H__
#define __LETTER_BUTTON_H__

#include <string>
#include <list>
#include <SFML/Graphics.hpp>

#include "fe/types/BasicTypes.h"
#include "fe/types/Alignment.h"
#include "fe/utils/TransformableUtils.h"

namespace fe
{

class LetterButton;

typedef std::list<LetterButton> TLetterButtonList;

class LetterButton
{
private:
	sf::Text 		   m_Letter;
	sf::RectangleShape m_Button;

	void Copy(const LetterButton& toCopy);
	void FitLetter(const F32 letterScale);

public:
	LetterButton(const wchar_t letter, const sf::Font& font,
		const sf::Vector2f& buttonSize, F32 letterScale);
	LetterButton(const LetterButton& toCopy);
	LetterButton& operator=(const LetterButton& toCopy);
	~LetterButton();

	void Draw(sf::RenderWindow& window) const;

	void SetPosition(const sf::Vector2f& position);
};

}

#endif
