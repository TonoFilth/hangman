#ifndef __POINTER_TYPES_H__
#define __POINTER_TYPES_H__

#include <memory>
#include <SFML/Graphics.hpp>

#include "kompex/KompexSQLiteDatabase.h"

typedef std::shared_ptr<sf::Font>	 TFontPtr;
typedef std::shared_ptr<sf::Texture> TTexturePtr;

typedef std::shared_ptr<Kompex::SQLiteDatabase> TDatabasePtr;

#endif