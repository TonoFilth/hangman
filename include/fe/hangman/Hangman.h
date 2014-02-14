#ifndef __HANGMAN_H__
#define __HANGMAN_H__

#include <memory>
#include "fe/hangman/BodyPart.h"

namespace fe
{

class Hangman;

typedef std::vector<sf::Sprite>  TSpriteVec;
typedef std::shared_ptr<Hangman> THangmanShPtr;

class Hangman
{

friend class HangmanFactory;

private:
	UI32 		 m_LastShown;
	TSpriteVec   m_Hangman;
	sf::Texture  m_Texture;

	Hangman(const Hangman& toCopy);
	Hangman& operator=(const Hangman& toCopy);
	Hangman();
	~Hangman();
	
public:
	bool ShowNextBodyPart();
	void HideAllBodyParts();
	void Draw(sf::RenderWindow& window) const;

	void SetPosition(const sf::Vector2f& position);
	void PrintDebug(const std::string& spaces = "") const;
};

}

#endif
