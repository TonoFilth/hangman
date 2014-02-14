#ifndef __JSON_BODY_PART_EXTRACTOR_H__
#define __JSON_BODY_PART_EXTRACTOR_H__

#include "fe/hangman/factory/IBodyPartExtractor.h"

namespace fe
{

class JsonBodyPartExtractor : public IBodyPartExtractor
{
private:
	JsonBodyPartExtractor(const JsonBodyPartExtractor& toCopy);
	JsonBodyPartExtractor& operator=(const JsonBodyPartExtractor& toCopy);

public:
	JsonBodyPartExtractor();
	~JsonBodyPartExtractor();

	virtual bool Extract(const std::string& fileName, std::string& txFileNameOut,
		TBodyPartVec& bodyPartsOut);
};

}

#endif
