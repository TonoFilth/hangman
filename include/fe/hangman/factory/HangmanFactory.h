#ifndef __HANGMAN_FACTORY_H__
#define __HANGMAN_FACTORY_H__

#include <iostream>

#include "fe/hangman/Hangman.h"
#include "fe/hangman/factory/IBodyBuilder.h"
#include "fe/hangman/factory/IBodyPartExtractor.h"
#include "fe/hangman/factory/BodyPartChecker.h"

namespace fe
{

class HangmanFactory
{
private:
	TBodyBuilderPtr 	  m_BodyBuilder;
	TBodyPartExtractorPtr m_BodyPartExtractor;

	HangmanFactory(const HangmanFactory& toCopy);
	HangmanFactory& operator=(const HangmanFactory& toCopy);

public:
	HangmanFactory(const TBodyPartExtractorPtr& bpExtractor,
				   const TBodyBuilderPtr& 	    bodyBuilder);
	~HangmanFactory();

	THangmanShPtr Create();
};

}

#endif
