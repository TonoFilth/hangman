#include "fe/hangman/BodyPart.h"

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

BodyPart::~BodyPart()
{
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

}
