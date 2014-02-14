#ifndef __HANGMAN_H__
#define __HANGMAN_H__

#include "fe/hangman/BodyPart.h"
#include "fe/hangman/BodyPartChecker.h"
#include "fe/hangman/BodyBuilder.h"

namespace fe
{

typedef std::vector<sf::Sprite> TSpriteVec;

class Hangman
{
private:
	sf::Texture  m_Texture;
	TBodyPartVec m_BodyParts;
	TSpriteVec   m_Hangman;

	Hangman(const Hangman& toCopy);
	Hangman& operator=(const Hangman& toCopy);

public:
	Hangman(const std::string& textureFile);
	~Hangman();

	bool BuildFromBodyParts(const TBodyPartVec& bodyParts,
		const sf::Vector2f& position = sf::Vector2f(0, 0));
	void Draw(sf::RenderWindow& window) const;

	void PrintDebug(const std::string& spaces = "") const;
};

}

#endif
