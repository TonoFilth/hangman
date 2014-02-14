#include "fe/hangman/BodyBuilder.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	PRIVATE AND PROTECTED METHODS
// =============================================================================
void BodyBuilder::BuildBodyPart(const TBodyPartVec& bodyParts, const BodyPart& bodyPart,
	const sf::Texture& texture, const Joint& joint, const sf::Vector2f& parentCoords,
	TSpriteVec& body)
{
	Vector2f jCoords(joint.GetCoords());
	Vector2f bpCoords(parentCoords.x + jCoords.x, parentCoords.y + jCoords.y);
	Vector2f bpRelativeCoords(bpCoords);

	Sprite bpSprite(texture, bodyPart.GetTextureCoords());
	auto bounds = bpSprite.getLocalBounds();
	Vector2f origin(bounds.left, bounds.top);

	switch (joint.GetHorizontalAlignment())
	{
		case THAlign::LEFT   : origin.x = 0; break;
		case THAlign::CENTER : origin.x = bounds.width * 0.5; bpRelativeCoords.x -= origin.x; break;
		case THAlign::RIGHT  : origin.x = bounds.width; bpRelativeCoords.x -= origin.x; break;
		default : cerr << "ERROR: Bad horizontal alignment" << endl; break;
	}

	switch (joint.GetVerticalAlignment())
	{
		case TVAlign::TOP    : origin.y = 0; break;
		case TVAlign::CENTER : origin.y = bounds.height * 0.5; bpRelativeCoords.y -= origin.y; break;
		case TVAlign::BOTTOM : origin.y = bounds.height; bpRelativeCoords.y -= origin.y; break;
		default : cerr << "ERROR: Bad vertical alignment" << endl; break;
	}

	bpSprite.setOrigin(origin);
	bpSprite.setPosition(bpCoords);
	body.push_back(bpSprite);

	for (auto& joint : bodyPart.GetJoints())
	{
		BuildBodyPart(bodyParts, FindBodyPartByOrder(bodyParts, joint.GetOrder()),
			texture, joint, bpRelativeCoords, body);
	}
}

// =============================================================================
//	STATIC METHODS
// =============================================================================
void BodyBuilder::Build(const TBodyPartVec& bodyParts, const sf::Texture& texture,
		const Vector2f& position, TSpriteVec& body)
{
	// Clear the body vector
	body.clear();

	// Get root body part
	BodyPart root(FindBodyPartByOrder(bodyParts, K_ROOT_ORDER));
	Sprite rootSprite(texture, root.GetTextureCoords());

	rootSprite.setPosition(position);
	body.push_back(rootSprite);

	for (auto& joint : root.GetJoints())
		BuildBodyPart(bodyParts, FindBodyPartByOrder(bodyParts, joint.GetOrder()),
			texture, joint, position, body);
}

}
