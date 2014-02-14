#ifndef __CHARACTER_BUTTON_H__
#define __CHARACTER_BUTTON_H__

#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>

namespace fe
{

class CharacterButton;

typedef std::list<CharacterButton> TCharacterButtonList;

class CharacterButton
{
private:
	sf::Text 		   m_Character;
	sf::RectangleShape m_Button;

	void Copy(const CharacterButton& toCopy);

public:
	CharacterButton(const sf::Font& font, const sf::String& character,
		const sf::Color& color = sf::Color::White);
	CharacterButton(const CharacterButton& toCopy);
	CharacterButton& operator=(const CharacterButton& toCopy);
	~CharacterButton();

	void Draw(sf::RenderWindow& window) const;

	sf::FloatRect GetBounds() const;
	sf::Vector2f GetPosition() const;

	void SetPosition(const sf::Vector2f& position);
	void SetCharacter(const sf::String& character);
	void SetColor(const sf::Color& color);
};

}

#endif
