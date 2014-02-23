#ifndef __IBODY_BUILDER_H__
#define __IBODY_BUILDER_H__

#include <memory>
#include "fe/hangman/BodyPart.h"

namespace fe
{

class IBodyBuilder;

typedef std::vector<sf::Sprite> 	  TSpriteVec;
typedef std::shared_ptr<IBodyBuilder> TBodyBuilderPtr;

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
