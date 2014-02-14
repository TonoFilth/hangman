#include "fe/hangman/factory/OrderedBodyBuilder.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
OrderedBodyBuilder::OrderedBodyBuilder()
{
}

OrderedBodyBuilder::~OrderedBodyBuilder()
{
}

// =============================================================================
//	PRIVATE AND PROTECTED METHODS
// =============================================================================
Vector2f OrderedBodyBuilder::GetBodyPartOrigin(const Joint& joint,
	const FloatRect& bpSpriteBounds) const
{
	Vector2f origin(bpSpriteBounds.left, bpSpriteBounds.top);

	switch (joint.GetHorizontalAlignment())
	{
		case THAlign::LEFT   : origin.x = 0; break;
		case THAlign::CENTER : origin.x = bpSpriteBounds.width * 0.5; break;
		case THAlign::RIGHT  : origin.x = bpSpriteBounds.width; break;
		default : cerr << "ERROR: Bad horizontal alignment" << endl; break;
	}

	switch (joint.GetVerticalAlignment())
	{
		case TVAlign::TOP    : origin.y = 0; break;
		case TVAlign::CENTER : origin.y = bpSpriteBounds.height * 0.5; break;
		case TVAlign::BOTTOM : origin.y = bpSpriteBounds.height; break;
		default : cerr << "ERROR: Bad vertical alignment" << endl; break;
	}

	return origin;
}

void OrderedBodyBuilder::BuildBodyPart(const BodyPart& bodyPart, const Joint& joint,
	const sf::Vector2f& parentCoords)
{
	Vector2f jCoords(joint.GetCoords());
	Vector2f bpCoords(parentCoords.x + jCoords.x, parentCoords.y + jCoords.y);

	Sprite bpSprite(*m_Texture, bodyPart.GetTextureCoords());
	Vector2f origin(GetBodyPartOrigin(joint, bpSprite.getLocalBounds()));

	Vector2f bpRelativeCoords(bpCoords);
	bpRelativeCoords -= origin;

	bpSprite.setOrigin(origin);
	bpSprite.setPosition(bpCoords);
	m_BodySprite->push_back(bpSprite);

	for (auto& joint : bodyPart.GetJoints())
		BuildBodyPart(FindBodyPartByOrder(*m_BodyParts, joint.GetOrder()),
			joint, bpRelativeCoords);
}

// =============================================================================
//	VIRTUAL METHODS
// =============================================================================
bool OrderedBodyBuilder::Build(const TBodyPartVec& bodyParts,
	const Texture& texture, TSpriteVec& bodyOut)
{
	m_Texture    = &texture;
	m_BodyParts  = &bodyParts;
	m_BodySprite = &bodyOut;
	m_BodySprite->clear();

	// Get root body part
	BodyPart root(FindBodyPartByOrder(*m_BodyParts, K_ROOT_ORDER));
	Sprite rootSprite(*m_Texture, root.GetTextureCoords());

	Vector2f defPosition(0, 0);
	rootSprite.setPosition(defPosition);
	m_BodySprite->push_back(rootSprite);

	for (auto& joint : root.GetJoints())
		BuildBodyPart(FindBodyPartByOrder(*m_BodyParts, joint.GetOrder()),
			joint, defPosition);

	return true;
}

}
