#ifndef __UI_TYPES_H__
#define __UI_TYPES_H__

#include <SFML/Graphics.hpp>

#include "fe/types/BasicTypes.h"
#include "fe/types/AlignmentTypes.h"
#include "fe/types/PointerTypes.h"

namespace fe
{

enum class Fitting
{
	HORIZONTAL,
	VERTICAL,
	BOTH
};

typedef Fitting TFit;

struct Layout
{
	// Empty ctor
	Layout() :
		Layout(0, TAlignment(THAlign::LEFT, TVAlign::TOP),
			sf::FloatRect(0, 0, 0, 0), sf::FloatRect(0, 0, 0, 0))
	{
	}

	// Padding & margin ctor
	Layout(const sf::FloatRect& p, const sf::FloatRect& m) :
		Layout(0, TAlignment(THAlign::LEFT, TVAlign::TOP), p, m)
	{
	}

	// Padding , margin & alignment ctor
	Layout(const sf::FloatRect& p, const sf::FloatRect& m, const TAlignment& a) :
		Layout(0, a, p, sf::FloatRect(0, 0, 0, 0))
	{
	}

	// Full ctor
	Layout(const F32 l, const TAlignment& a,
		const sf::FloatRect& p, const sf::FloatRect& m) :
			lineHeight(l), alignment(a), padding(p), margin(m)
	{
	}

	F32      	  lineHeight;
	TAlignment 	  alignment;
	sf::FloatRect padding;
	sf::FloatRect margin;
};

typedef Layout TLayout;

struct Style
{
	Style(const TFontPtr& f = nullptr, const sf::Color c = sf::Color::Black,
		  const sf::Vector2f& s = sf::Vector2f(1.0, 1.0), const TFit fi = TFit::BOTH,
		  const TLayout& l = TLayout()) :
		font(f), color(c), scale(s), fit(fi), layout(l)
	{
	}

	TFontPtr  	 font;
	sf::Color 	 color;
	sf::Vector2f scale;
	TFit 		 fit;
	TLayout 	 layout;
};

typedef Style TStyle;

}

#endif