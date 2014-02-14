#include "fe/hangman/BodyPart.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
BodyPart::BodyPart(UI32 bOrder, const sf::IntRect& txCoords) :
	m_Order(bOrder),
	m_TxCoords(txCoords)
{
}

BodyPart::BodyPart(const BodyPart& toCopy)
{
	Copy(toCopy);
}

BodyPart& BodyPart::operator=(const BodyPart& toCopy)
{
	if (this == &toCopy)
		return *this;

	Copy(toCopy);

	return *this;
}

BodyPart::~BodyPart()
{
}

// =============================================================================
//	PRIVATE AND PROTECTED METHODS
// =============================================================================
void BodyPart::Copy(const BodyPart& toCopy)
{
	m_Order    = toCopy.m_Order;
	m_TxCoords = toCopy.m_TxCoords;
	m_Joints   = toCopy.m_Joints;
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
void BodyPart::AddJoint(const Joint& joint)
{
	m_Joints.push_back(joint);
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
UI32 BodyPart::GetOrder() const
{
	return m_Order;
}

IntRect BodyPart::GetTextureCoords() const
{
	return m_TxCoords;
}

TOrderVec BodyPart::GetJointOrders() const
{
	TOrderVec orders;

	for (auto& joint : m_Joints)
		orders.push_back(joint.GetOrder());

	return orders;
}

TJointVec BodyPart::GetJoints() const
{
	return m_Joints;
}

// =============================================================================
//	DEBUG METHODS
// =============================================================================
void BodyPart::PrintDebug(const std::string& spaces) const
{
	cout << spaces << "BodyPart " << endl;
	cout << spaces << "  Order:    " << m_Order << endl;
	cout << spaces << "  TxCoords: LT: (";
	cout << m_TxCoords.left << " , " << m_TxCoords.top << ")";
	cout << " WH: (";
	cout << m_TxCoords.width << " , " << m_TxCoords.height << ")" << endl;

	for (auto& joint : m_Joints)
		joint.PrintDebug(spaces + "  ");
}

}
