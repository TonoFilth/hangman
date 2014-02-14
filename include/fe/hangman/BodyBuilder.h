#ifndef __BODY_BUILDER_H__
#define __BODY_BUILDER_H__

#include "fe/hangman/BodyPart.h"

namespace fe
{

typedef std::vector<sf::Sprite> TSpriteVec;

class BodyBuilder
{
private:
	BodyBuilder();
	BodyBuilder(const BodyBuilder& toCopy);
	BodyBuilder& operator=(const BodyBuilder& toCopy);
	~BodyBuilder();

	static void BuildBodyPart(const TBodyPartVec& bodyParts,
		const BodyPart& bodyPart, const sf::Texture& texture,
		const Joint& joint, const sf::Vector2f& parentCoords,
		TSpriteVec& body);

public:
	static void Build(const TBodyPartVec& bodyParts, const sf::Texture& texture,
		const sf::Vector2f& position, TSpriteVec& body);
};

}

#endif
