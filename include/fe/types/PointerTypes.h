#ifndef __POINTER_TYPES_H__
#define __POINTER_TYPES_H__

#include <memory>
#include <SFML/Graphics.hpp>

typedef std::shared_ptr<sf::Font>	 TFontPtr;
typedef std::shared_ptr<sf::Texture> TTexturePtr;

#endif