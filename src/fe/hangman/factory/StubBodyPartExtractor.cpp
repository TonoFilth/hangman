#include "fe/hangman/factory/StubBodyPartExtractor.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
StubBodyPartExtractor::StubBodyPartExtractor()
{
}

StubBodyPartExtractor::~StubBodyPartExtractor()
{
}

// =============================================================================
//	VIRTUAL METHODS
// =============================================================================
bool StubBodyPartExtractor::Extract(string& txFileNameOut, TBodyPartVec& bodyPartsOut)
{
	BodyPart head(0, IntRect(0, 0, 28, 28));
	BodyPart body(1, IntRect(0, 28, 5, 50));
	BodyPart larm(2, IntRect(6, 28, 30, 19));
	BodyPart rarm(3, IntRect(35, 28, 30, 19));
	BodyPart lleg(4, IntRect(6, 47, 30, 19));
	BodyPart rleg(5, IntRect(35, 47, 30, 19));

	// Joints
	Joint headJoint(1, Vector2f(14, 28), THAlign::CENTER , TVAlign::TOP);
	Joint bodyJointLarm(2, Vector2f(3, 14), THAlign::RIGHT , TVAlign::BOTTOM);
	Joint bodyJointRarm(3, Vector2f(3, 14), THAlign::LEFT , TVAlign::BOTTOM);
	Joint bodyJointLleg(4, Vector2f(3, 48), THAlign::RIGHT , TVAlign::TOP);
	Joint bodyJointRleg(5, Vector2f(3, 48), THAlign::LEFT , TVAlign::TOP);

	// Association Joint -> BodyPart
	head.AddJoint(headJoint);
	body.AddJoint(bodyJointLarm);
	body.AddJoint(bodyJointRarm);
	body.AddJoint(bodyJointLleg);
	body.AddJoint(bodyJointRleg);

	txFileNameOut = "assets/images/hangman.png";

	bodyPartsOut.push_back(head);
	bodyPartsOut.push_back(body);
	bodyPartsOut.push_back(larm);
	bodyPartsOut.push_back(rarm);
	bodyPartsOut.push_back(lleg);
	bodyPartsOut.push_back(rleg);

	return true;
}

}
