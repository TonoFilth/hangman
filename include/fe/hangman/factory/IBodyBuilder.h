#ifndef __IBODY_BUILDER_H__
#define __IBODY_BUILDER_H__

#include "fe/hangman/BodyPart.h"

namespace fe
{

typedef std::vector<sf::Sprite> TSpriteVec;

class IBodyBuilder
{
private:
	IBodyBuilder(const IBodyBuilder& toCopy);
	IBodyBuilder& operator=(const IBodyBuilder& toCopy);

public:
	IBodyBuilder() 			{}
	virtual ~IBodyBuilder() {}

	virtual bool Build(const TBodyPartVec& bodyParts,
		const sf::Texture& texture, TSpriteVec& bodyOut) = 0;
};

}

#endif
