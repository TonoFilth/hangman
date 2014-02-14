#include <iostream>
#include "fe/hangman/Hangman.h"

using namespace std;
using namespace sf;
using namespace fe;

int main(int argc, char** argv)
{
	/*
	// Body parts
	BodyPart head(0, IntRect(0, 0, 35, 28));
	BodyPart body(1, IntRect(0, 36, 5, 50));
	BodyPart larm(2, IntRect(6, 29, 30, 19));
	BodyPart rarm(3, IntRect(6, 48, 34, 19));
	BodyPart lleg(4, IntRect(36, 29, 30, 23));
	BodyPart rleg(5, IntRect(36, 48, 34, 23));

	// Joints
	Joint headJoint(1, Vector2f(17, 28));
	Joint bodyJointLarm(2, Vector2f(3, 14));
	Joint bodyJointRarm(3, Vector2f(3, 14));
	Joint bodyJointLleg(4, Vector2f(3, 48));
	Joint bodyJointRleg(5, Vector2f(3, 48));

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

	// Body parts
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

	hangman.BuildFromBodyParts(bpVec, Vector2f(250, 250));
	hangman.PrintDebug();

	RenderWindow window(VideoMode(500, 500), "Hangman");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
			if (event.type == Event::Closed)
				window.close();

		window.clear(Color::White);
		hangman.Draw(window);
		window.display();
	}

	return 0;
}