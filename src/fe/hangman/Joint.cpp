#include "fe/hangman/Joint.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTANTS
// =============================================================================
const UI32 K_ROOT_ORDER    = 0;
const UI32 K_INVALID_ORDER = 666;
const Joint InvalidJoint(K_INVALID_ORDER, Vector2f(0, 0));

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
Joint::Joint(UI32 jOrder, const Vector2f& jCoords,
	const THAlign hAlign, const TVAlign vAlign) :
	m_Order(jOrder),
	m_Coords(jCoords),
	m_HAlign(hAlign),
	m_VAlign(vAlign)
{
}

Joint::Joint(const Joint& toCopy)
{
	Copy(toCopy);
}

Joint& Joint::operator=(const Joint& toCopy)
{
	if (this == &toCopy)
		return *this;

	Copy(toCopy);

	return *this;
}

Joint::~Joint()
{
}

// =============================================================================
//	PRIVATE AND PROTECTED METHODS
// =============================================================================
void Joint::Copy(const Joint& toCopy)
{
	m_Order  = toCopy.m_Order;
	m_Coords = toCopy.m_Coords;
	m_HAlign = toCopy.m_HAlign;
	m_VAlign = toCopy.m_VAlign;
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
UI32 Joint::GetOrder() const
{
	return m_Order;
}

Vector2f Joint::GetCoords() const
{
	return m_Coords;
}

THAlign Joint::GetHorizontalAlignment() const
{
	return m_HAlign;
}

TVAlign Joint::GetVerticalAlignment() const
{
	return m_VAlign;
}

// =============================================================================
//	QUESTION METHODS
// =============================================================================
bool Joint::IsValid() const
{
	return m_Order != InvalidJoint.m_Order;
}

// =============================================================================
//	DEBUG METHODS
// =============================================================================
void Joint::PrintDebug(const std::string& spaces) const
{
	cout << spaces << "Joint" << endl;
	cout << spaces << "  Order:   " << m_Order << endl;
	cout << spaces << "  Coords:  (" << m_Coords.x << " , " << m_Coords.y << ")" << endl;
	cout << spaces << "  H-Align: ";

	switch (m_HAlign)
	{
		case THAlign::LEFT   : cout << "\"left\"";   break;
		case THAlign::CENTER : cout << "\"center\""; break;
		case THAlign::RIGHT  : cout << "\"right\"";  break;
		default : cout << "** ERROR **"; break;
	}

	cout << endl << spaces << "  V-Align: ";

	switch (m_VAlign)
	{
		case TVAlign::TOP 	 : cout << "\"top\"";    break;
		case TVAlign::CENTER : cout << "\"center\""; break;
		case TVAlign::BOTTOM : cout << "\"bottom\""; break;
		default : cout << "** ERROR **"; break;
	}

	cout << endl;
}

}
