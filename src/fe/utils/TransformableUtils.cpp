#include "fe/utils/TransformableUtils.h"

using namespace std;
using namespace sf;

namespace fe
{

static Vector2f GetOrigin(const FloatRect& bounds, const THAlign hAlign,
	const TVAlign vAlign)
{
	Vector2f origin(0, 0);

	switch (hAlign)
	{
		case THAlign::LEFT   : origin.x = 0; break;
		case THAlign::CENTER : origin.x = (bounds.left + bounds.width) * 0.5; break;
		case THAlign::RIGHT  : origin.x = bounds.left + bounds.width; break;
		default : cerr << "ERROR: Bad horizontal alignment" << endl; break;
	}

	switch (vAlign)
	{
		case TVAlign::TOP    : origin.y = 0; break;
		case TVAlign::CENTER : origin.y = (bounds.top + bounds.height) * 0.5; break;
		case TVAlign::BOTTOM : origin.y = bounds.top + bounds.height; break;
		default : cerr << "ERROR: Bad vertical alignment" << endl; break;
	}

	return origin;
}

void TransformableSetOrigin(Text& t, const THAlign hAlign, const TVAlign vAlign)
{
	auto origin(GetOrigin(t.getLocalBounds(), hAlign, vAlign));
	t.setOrigin(origin);
}

void TransformableSetOrigin(Shape& s, const THAlign hAlign, const TVAlign vAlign)
{
	auto origin(GetOrigin(s.getLocalBounds(), hAlign, vAlign));
	s.setOrigin(origin);
}

/*
void TransformableSetOrigin(FloatRect& tBounds, const THAlign hAlign,
	const TVAlign vAlign)
{
	return setOrigin(tBounds);
}*/

void TransformableAlignRelative(Transformable& toAlign, const RectangleShape& relativeTo,
	const THAlign hAlign, const TVAlign vAlign)
{
	auto rSize = relativeTo.getSize();
	auto rPos  = relativeTo.getPosition();
	auto aPos  = rPos;

	switch (hAlign)
	{
		case THAlign::LEFT   : break;
		case THAlign::CENTER : aPos.x += rSize.x * 0.5; break;
		case THAlign::RIGHT  : aPos.x += rSize.x; break;
		default : cerr << "ERROR: Bad horizontal alignment" << endl; break;
	}

	switch (vAlign)
	{
		case TVAlign::TOP    : break;
		case TVAlign::CENTER : aPos.y += rSize.y * 0.5; break;
		case TVAlign::BOTTOM : aPos.y += rSize.y; break;
		default : cerr << "ERROR: Bad vertical alignment" << endl; break;
	}

	toAlign.setPosition(aPos);
}

sf::Vector2f TransformableGetPositionAligned(const sf::Vector2f& desiredPosition,
	const sf::Vector2f& objectSize, const TAlignment& alignment)
{
	Vector2f finalPos(desiredPosition);

	switch (alignment.h)
	{
		case THAlign::LEFT   : break;
		case THAlign::CENTER : finalPos.x -= objectSize.x * 0.5; break;
		case THAlign::RIGHT  : finalPos.x -= objectSize.x; break;
		default : cerr << "ERROR: Bad horizontal alignment" << endl; break;
	}

	switch (alignment.v)
	{
		case TVAlign::TOP    : break;
		case TVAlign::CENTER : finalPos.y -= objectSize.y * 0.5; break;
		case TVAlign::BOTTOM : finalPos.y -= objectSize.y; break;
		default : cerr << "ERROR: Bad vertical alignment" << endl; break;
	}

	return finalPos;
}

}