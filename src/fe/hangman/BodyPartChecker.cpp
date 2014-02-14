#include "fe/hangman/BodyPartChecker.h"

using namespace std;

namespace fe
{

// =============================================================================
//	CONSTANTS
// =============================================================================
const UI32 K_ROOT_ORDER = 0;

// =============================================================================
//	STATIC METHODS
// =============================================================================
bool BodyPartChecker::Check(const TBodyPartVec& bodyParts)
{
	TOrderVec bodyPartOrders;

	// Check that body part orders are unique
	if (!CheckBodyParts(bodyParts, bodyPartOrders))
		return false;

	// Check if root body part is present
	if (find(bodyPartOrders.begin(), bodyPartOrders.end(),
		K_ROOT_ORDER) == bodyPartOrders.end())
	{
		cerr << "ERROR: Root body part(" << K_ROOT_ORDER << ") not found" << endl;
		return false;
	}

	TOrderVec jointOrders;

	// Check that joint orders are unique
	for (auto& bodyPart : bodyParts)
		if (!CheckJoints(bodyPart, jointOrders))
			return false;

	CheckMissingReferences(bodyParts, bodyPartOrders, jointOrders);

	return true;
}

// =============================================================================
//	PRIVATE AND PROTECTED METHODS
// =============================================================================
bool BodyPartChecker::CheckBodyParts(const TBodyPartVec& bodyParts, TOrderVec& orders)
{
	for (auto& bodyPart : bodyParts)
		if (find(orders.begin(), orders.end(), bodyPart.GetOrder()) != orders.end())
			return false;
		else
			orders.push_back(bodyPart.GetOrder());

	return true;
}

bool BodyPartChecker::CheckJoints(const BodyPart& bodyPart, TOrderVec& orders)
{
	for (auto& joint : bodyPart.GetJoints())
		if (find(orders.begin(), orders.end(), joint.GetOrder()) != orders.end())
			return false;
		else
			orders.push_back(joint.GetOrder());

	return true;
}

void BodyPartChecker::CheckMissingReferences(const TBodyPartVec& bodyParts,
	const TOrderVec& bpOrders, const TOrderVec& jOrders)
{
	// Check for unassigned body parts
	for (auto& bodyPart : bodyParts)
	{
		if (find(jOrders.begin(), jOrders.end(),
			bodyPart.GetOrder()) == jOrders.end() &&
			bodyPart.GetOrder() != K_ROOT_ORDER)
		{
			cout << "WARNING: Body part " << bodyPart.GetOrder();
			cout << " not referenced by any joint" << endl;
		}
	}

	// Check for unassigned joints
	for (auto& bodyPart : bodyParts)
	{
		for (auto& joint : bodyPart.GetJoints())
		{
			if (find(bpOrders.begin(), bpOrders.end(),
				joint.GetOrder()) == bpOrders.end())
			{
				cout << "WARNING: Undefined body part " << joint.GetOrder();
				cout << " from joint of body part " << bodyPart.GetOrder() << endl;
			}
		}
	}
}

}
