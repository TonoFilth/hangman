#ifndef __STUB_BODY_PART_EXTRACTOR_H__
#define __STUB_BODY_PART_EXTRACTOR_H__

#include "fe/hangman/factory/IBodyPartExtractor.h"

namespace fe
{

class StubBodyPartExtractor : public IBodyPartExtractor
{
private:
	StubBodyPartExtractor(const StubBodyPartExtractor& toCopy);
	StubBodyPartExtractor& operator=(const StubBodyPartExtractor& toCopy);

public:
	StubBodyPartExtractor();
	~StubBodyPartExtractor();

	virtual bool Extract(std::string& txFileNameOut, TBodyPartVec& bodyPartsOut);
};

}

#endif
