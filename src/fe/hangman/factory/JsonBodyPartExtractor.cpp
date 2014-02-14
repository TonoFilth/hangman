#include "fe/hangman/factory/JsonBodyPartExtractor.h"

using namespace std;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
JsonBodyPartExtractor::JsonBodyPartExtractor()
{
}

JsonBodyPartExtractor::~JsonBodyPartExtractor()
{
}

// =============================================================================
//	VIRTUAL METHODS
// =============================================================================
bool JsonBodyPartExtractor::Extract(const string& fileName, string& txFileNameOut,
		TBodyPartVec& bodyPartsOut)
{
	return false;
}

}
