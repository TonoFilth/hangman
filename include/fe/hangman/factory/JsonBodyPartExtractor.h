#ifndef __JSON_BODY_PART_EXTRACTOR_H__
#define __JSON_BODY_PART_EXTRACTOR_H__

#include <string.h>
#include <sstream>
#include <iterator>
#include <SFML/Graphics.hpp>

#include "cJSON/cJSON.h"
#include "fe/hangman/factory/IBodyPartExtractor.h"
#include "fe/utils/FileUtils.h"

namespace fe
{

class JsonBodyPartExtractor : public IBodyPartExtractor
{
private:
	std::string m_FileName;

	Joint ParseJoint(cJSON* joint) const;
	TJointVec ParseJoints(cJSON* joints) const;
	BodyPart ParseBodyPart(cJSON* bodyPart) const;

	sf::Vector2f StringToVector2f(const std::string& str) const;
	sf::IntRect StringToIntRect(const std::string& str) const;

	JsonBodyPartExtractor(const JsonBodyPartExtractor& toCopy);
	JsonBodyPartExtractor& operator=(const JsonBodyPartExtractor& toCopy);

public:
	JsonBodyPartExtractor(const std::string& fileName);
	~JsonBodyPartExtractor();

	virtual bool Extract(std::string& txFileNameOut, TBodyPartVec& bodyPartsOut);
};

}

#endif
