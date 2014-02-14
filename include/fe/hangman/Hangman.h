#ifndef __HANGMAN_H__
#define __HANGMAN_H__

#include "fe/hangman/BodyPart.h"

namespace fe
{

typedef std::vector<BodyPart> 	TBodyPartVec;
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

	void BuildFromBodyParts(const TBodyPartVec& bodyParts);
	void Draw(sf::RenderWindow& window) const;

	void PrintDebug(const std::string& spaces = "") const;
};

}

#endif
