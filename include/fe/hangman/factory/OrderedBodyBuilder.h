#ifndef __ORDERED_BODY_BUILDER_H__
#define __ORDERED_BODY_BUILDER_H__

#include "fe/hangman/factory/IBodyBuilder.h"

namespace fe
{

class OrderedBodyBuilder : public IBodyBuilder
{
private:
	const sf::Texture*  m_Texture;
	const TBodyPartVec* m_BodyParts;
	TSpriteVec*   m_BodySprite;

	sf::Vector2f GetBodyPartOrigin(const Joint& joint,
		const sf::FloatRect& bpSpriteBounds) const;

	void BuildBodyPart(const BodyPart& bodyPart, const Joint& joint,
		const sf::Vector2f& parentCoords);

	OrderedBodyBuilder(const OrderedBodyBuilder& toCopy);
	OrderedBodyBuilder& operator=(const OrderedBodyBuilder& toCopy);

public:
	OrderedBodyBuilder();
	~OrderedBodyBuilder();

	virtual bool Build(const TBodyPartVec& bodyParts,
		const sf::Texture& texture, TSpriteVec& bodyOut);
};

}

#endif
