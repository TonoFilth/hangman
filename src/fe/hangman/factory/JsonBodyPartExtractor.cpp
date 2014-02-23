#include "fe/hangman/factory/JsonBodyPartExtractor.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
JsonBodyPartExtractor::JsonBodyPartExtractor(const string& fileName) :
	m_FileName(fileName)
{
}

JsonBodyPartExtractor::~JsonBodyPartExtractor()
{
}

// =============================================================================
//	PRIVATE AND PROTECTED METHODS
// =============================================================================
Joint JsonBodyPartExtractor::ParseJoint(cJSON* jointNode) const
{
	UI32 order;
	Vector2f coords;
	THAlign hAlign;
	TVAlign vAlign;

	bool orderSet, coordsSet;
	orderSet = coordsSet = false;

	while (jointNode)
	{
		if (strcmp(jointNode->string, "order") == 0)
		{
			order = static_cast<UI32>(jointNode->valueint);
			orderSet = true;
		}

		if (strcmp(jointNode->string, "coords") == 0)
		{
			coords = StringToVector2f(string(jointNode->valuestring));
			coordsSet = true;
		}

		// Parse horizontal alignment
		if (strcmp(jointNode->string, "h-align") == 0)
		{
			if (strcmp(jointNode->valuestring, "left") == 0)
				hAlign = THAlign::LEFT;
			if (strcmp(jointNode->valuestring, "center") == 0)
				hAlign = THAlign::CENTER;
			if (strcmp(jointNode->valuestring, "right") == 0)
				hAlign = THAlign::RIGHT;
		}

		// Parse vertical alignment
		if (strcmp(jointNode->string, "v-align") == 0)
		{
			if (strcmp(jointNode->valuestring, "top") == 0)
				vAlign = TVAlign::TOP;
			if (strcmp(jointNode->valuestring, "center") == 0)
				vAlign = TVAlign::CENTER;
			if (strcmp(jointNode->valuestring, "bottom") == 0)
				vAlign = TVAlign::BOTTOM;
		}

		jointNode = jointNode->next;
	}

	if (!orderSet || !coordsSet)
	{
		cerr << "PARSE ERROR: Order and coords must be specified" << endl;
		return InvalidJoint;
	}

	return Joint(order, coords, hAlign, vAlign);
}

TJointVec JsonBodyPartExtractor::ParseJoints(cJSON* jointsNode) const
{
	TJointVec joints;
	Joint joint(InvalidJoint);

	while (jointsNode)
	{
		// Parse joint
		if (strcmp(jointsNode->string, "joint") == 0)
		{
			if (!(joint = ParseJoint(jointsNode->child)).IsValid())
				return TJointVec();
			else
				joints.push_back(joint);
		}

		jointsNode = jointsNode->next;
	}

	return joints;
}

BodyPart JsonBodyPartExtractor::ParseBodyPart(cJSON* bpNode) const
{
	UI32 order;
	IntRect txCoords;
	TJointVec joints;

	bool orderSet, txCoordsSet;
	orderSet = txCoordsSet = false;

	while (bpNode)
	{
		if (strcmp(bpNode->string, "order") == 0)
		{
			order = static_cast<UI32>(bpNode->valueint);
			orderSet = true;
		}

		if (strcmp(bpNode->string, "txCoords") == 0)
		{
			txCoords = StringToIntRect(string(bpNode->valuestring));
			txCoordsSet = true;
		}

		if (strcmp(bpNode->string, "joints") == 0 && (joints = ParseJoints(bpNode->child)).empty())
			return InvalidBodyPart;

		bpNode = bpNode->next;
	}

	if (!orderSet || !txCoordsSet)
	{
		cerr << "PARSE ERROR: Body part order and texture coords must be specified" << endl;
		return InvalidBodyPart;
	}

	BodyPart bp(order, txCoords);

	for (auto& joint : joints)
		bp.AddJoint(joint);

	return bp;
}

Vector2f JsonBodyPartExtractor::StringToVector2f(const string& str) const
{
	Vector2f coords(0, 0);

	istringstream is(str);
	is >> coords.x;
	is >> coords.y;

	return coords;
}

IntRect JsonBodyPartExtractor::StringToIntRect(const string& str) const
{
	IntRect coords(0, 0, 0, 0);

	istringstream is(str);
	is >> coords.left;
	is >> coords.top;
	is >> coords.width;
	is >> coords.height;

	return coords;
}

// =============================================================================
//	VIRTUAL METHODS
// =============================================================================
bool JsonBodyPartExtractor::Extract(string& txFileNameOut, TBodyPartVec& bodyPartsOut)
{
	string toParse;
	FileUtils::ReadLines(m_FileName, toParse);

	cJSON* root = cJSON_Parse(toParse.c_str());
	cJSON* child = root->child;
	
	bool textureSet, bodyPartsSet;
	BodyPart bp(InvalidBodyPart);

	textureSet = bodyPartsSet = false;

	while (child)
	{
		if (strcmp(child->string, "texture") == 0)
		{
			txFileNameOut = child->valuestring;
			textureSet = true;
		}

		if (strcmp(child->string, "bodypart") == 0)
		{
			if (!(bp = ParseBodyPart(child->child)).IsValid())
			{
				cerr << "PARSE ERROR: Malformed body part" << endl;
				return false;
			}
			else
			{
				bodyPartsOut.push_back(bp);
				bodyPartsSet = true;
			}
		}

		child = child->next;
	}

	if (!textureSet || !bodyPartsSet)
	{
		cerr << "PARSE ERROR: Hangman texture and at least one body part must be specified" << endl;
		return false;
	}

	return true;
}

}
