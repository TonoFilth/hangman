#include <iostream>
#include "fe/hangman/Hangman.h"

using namespace std;
using namespace sf;
using namespace fe;

void PrintOrderVec(const TOrderVec& vec)
{
	cout << "[ ";
	for (auto& order : vec)
		cout << order << " ";
	cout << "]" << endl;
}

void PrintIntRect(const IntRect& rect)
{
	cout << "[ ";
	cout << "L: " << rect.left << " ";
	cout << "T: " << rect.top << " ";
	cout << "W: " << rect.width << " ";
	cout << "H: " << rect.height << " ]" << endl;
}

void PrintJoint(const Joint& joint)
{
	cout << "  Joint" << endl;
	cout << "    Order:  " << joint.GetOrder() << endl;
	cout << "    Coords: " << "(" << joint.GetCoords().x << " , " << joint.GetCoords().y << ")" << endl;
}

void PrintBodyPart(const BodyPart& bodyPart)
{
	cout << "BodyPart " << bodyPart.GetOrder() << endl;
	cout << "  TxCoords: ";
	PrintIntRect(bodyPart.GetTextureCoords());

	for (auto& joint : bodyPart.GetJoints())
		PrintJoint(joint);
}

int main(int argc, char** argv)
{
	Joint j2(2, Vector2f(8, 8));
	Joint j3(3, Vector2f(16, 16));
	Joint j4(4, Vector2f(32, 32));

	BodyPart bp1(1, IntRect(0, 0, 16, 16));
	BodyPart bp2(2, IntRect(16, 0, 16, 16));

	bp1.AddJoint(j2);
	bp2.AddJoint(j3);
	bp2.AddJoint(j4);

	Hangman hangman("mytexture.png");
	TBodyPartVec bpVec;

	bpVec.push_back(bp1);
	bpVec.push_back(bp2);

	hangman.BuildFromBodyParts(bpVec);

	hangman.PrintDebug();

	return 0;
}