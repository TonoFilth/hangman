#ifndef __ALIGNMENT_TYPES_H__
#define __ALIGNMENT_TYPES_H__

namespace fe
{

enum class THAlign
{
	LEFT,
	CENTER,
	RIGHT
};

enum class TVAlign
{
	TOP,
	CENTER,
	BOTTOM
};

struct Alignment
{
	Alignment(const THAlign a, const TVAlign b) :
		h(a), v(b) {}
	
	THAlign h;
	TVAlign v;
};

typedef Alignment TAlignment;

}

#endif