#include <iostream>
#include "fe/hangman/Hangman.h"

using namespace std;
using namespace sf;
using namespace fe;

int main(int argc, char** argv)
{
	// Body parts
	/*BodyPart head(1, IntRect(0, 0, 35, 28));
	BodyPart body(2, IntRect(0, 36, 5, 50));
	BodyPart larm(3, IntRect(6, 29, 30, 19));
	BodyPart rarm(4, IntRect(6, 48, 34, 19));
	BodyPart lleg(5, IntRect(36, 29, 30, 23));
	BodyPart rleg(6, IntRect(36, 48, 34, 23));

	// Joints
	Joint headJoint(2, Vector2f(17, 28));
	Joint bodyJointLarm(3, Vector2f(3, 14));
	Joint bodyJointRarm(4, Vector2f(3, 14));
	Joint bodyJointLleg(5, Vector2f(3, 48));
	Joint bodyJointRleg(6, Vector2f(3, 48));

	// Association Joint -> BodyPart
	head.AddJoint(headJoint);
	body.AddJoint(bodyJointLarm);
	body.AddJoint(bodyJointRarm);
	body.AddJoint(bodyJointLleg);
	body.AddJoint(bodyJointRleg);

	// BodyPart vector
	TBodyPartVec bpVec;

	bpVec.push_back(head);
	bpVec.push_back(body);
	bpVec.push_back(larm);
	bpVec.push_back(rarm);
	bpVec.push_back(lleg);
	bpVec.push_back(rleg);

	// Hangman
	Hangman hangman("assets/images/hangman.png");

	hangman.BuildFromBodyParts(bpVec);
	hangman.PrintDebug();*/

	BodyPart bp1(0, IntRect(0, 0, 0, 0));
	BodyPart bp2(2, IntRect(0, 0, 0, 0));
	BodyPart bp3(4, IntRect(0, 0, 0, 0));

	Joint j1(2, Vector2f(0, 0));
	Joint j2(3, Vector2f(0, 0));

	bp1.AddJoint(j1);
	bp2.AddJoint(j2);

	TBodyPartVec bpVec;
	bpVec.push_back(bp1);
	bpVec.push_back(bp2);
	bpVec.push_back(bp3);

	Hangman hangman("assets/images/hangman.png");
	hangman.BuildFromBodyParts(bpVec);
	hangman.PrintDebug();

	return 0;
}