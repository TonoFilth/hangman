#ifndef __TRANSFORMABLE_UTILS_H__
#define __TRANSFORMABLE_UTILS_H__

#include <iostream>
#include <SFML/Graphics.hpp>

#include "fe/types/AlignmentTypes.h"

namespace fe
{

void TransformableSetOrigin(sf::Text& t, const THAlign hAlign, const TVAlign vAlign);
void TransformableSetOrigin(sf::Shape& s, const THAlign hAlign, const TVAlign vAlign);
void TransformableAlignRelative(sf::Transformable& toAlign,
	const sf::RectangleShape& relativeTo, const THAlign hAlign, const TVAlign vAlign);

sf::Vector2f TransformableGetPositionAligned(const sf::Vector2f& desiredPos,
	const sf::Vector2f& objectSize, const TAlignment& alignment);

}

#endif