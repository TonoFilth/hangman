#ifndef __CHARACTER_PICKER_H__
#define __CHARACTER_PICKER_H__

#include "fe/types/BasicTypes.h"
#include "fe/ui/CharacterButton.h"

namespace fe
{

class CharacterPicker
{
private:
	sf::Font 			 m_Font;
	TCharacterButtonList m_ButtonList;

	CharacterPicker(const CharacterPicker& toCopy);
	CharacterPicker& operator=(const CharacterPicker& toCopy);

public:
	CharacterPicker(const sf::Font& font);
	~CharacterPicker();

	void Draw(sf::RenderWindow& window) const;

	void SetCharacterList(const sf::String& characterList);
};

}

#endif
