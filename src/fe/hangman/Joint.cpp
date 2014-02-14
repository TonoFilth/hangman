#include "fe/hangman/Joint.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
Joint::Joint(UI32 jOrder, const Vector2f& jCoords) :
	m_Order(jOrder),
	m_Coords(jCoords)
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

// =============================================================================
//	DEBUG METHODS
// =============================================================================
void Joint::PrintDebug(const std::string& spaces) const
{
	cout << spaces << "Joint" << endl;
	cout << spaces << "  Order:  " << m_Order << endl;
	cout << spaces << "  Coords:  (" << m_Coords.x << " , " << m_Coords.y << ")" << endl;
}

}
