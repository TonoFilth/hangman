#ifndef __BODY_PART_EXTRACTOR_H__
#define __BODY_PART_EXTRACTOR_H__

#include <string>
#include <memory>

#include "fe/hangman/BodyPart.h"

namespace fe
{

class IBodyPartExtractor;

typedef std::shared_ptr<IBodyPartExtractor> TBodyPartExtractorPtr;

class IBodyPartExtractor
{
private:
	IBodyPartExtractor(const IBodyPartExtractor& toCopy);
	IBodyPartExtractor& operator=(const IBodyPartExtractor& toCopy);

public:
	IBodyPartExtractor() 		  {}
	virtual ~IBodyPartExtractor() {}

	virtual bool Extract(std::string& txFileNameOut, TBodyPartVec& bodyPartsOut) = 0;
};

}

#endif
