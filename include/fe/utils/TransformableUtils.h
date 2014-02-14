#ifndef __TRANSFORMABLE_UTILS_H__
#define __TRANSFORMABLE_UTILS_H__

#include <iostream>
#include <SFML/Graphics.hpp>

#include "fe/types/Alignment.h"

namespace fe
{

void TransformableSetOrigin(sf::Text& t, const THAlign hAlign, const TVAlign vAlign);
void TransformableSetOrigin(sf::Shape& s, const THAlign hAlign, const TVAlign vAlign);
void TransformableAlignRelative(sf::Transformable& toAlign,
	const sf::RectangleShape& relativeTo, const THAlign hAlign, const TVAlign vAlign);

}

#endif