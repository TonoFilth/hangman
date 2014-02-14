#ifndef __BODY_PART_EXTRACTOR_H__
#define __BODY_PART_EXTRACTOR_H__

#include <string>
#include "fe/hangman/BodyPart.h"

namespace fe
{

class IBodyPartExtractor
{
private:
	IBodyPartExtractor(const IBodyPartExtractor& toCopy);
	IBodyPartExtractor& operator=(const IBodyPartExtractor& toCopy);

public:
	IBodyPartExtractor() 		  {}
	virtual ~IBodyPartExtractor() {}

	virtual bool Extract(const std::string& fileName, std::string& txFileNameOut,
		TBodyPartVec& bodyPartsOut) = 0;
};

}

#endif
