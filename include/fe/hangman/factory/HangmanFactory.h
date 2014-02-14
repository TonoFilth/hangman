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
	IBodyBuilder* 		m_BodyBuilder;
	IBodyPartExtractor* m_BodyPartExtractor;

	HangmanFactory(const HangmanFactory& toCopy);
	HangmanFactory& operator=(const HangmanFactory& toCopy);

public:
	HangmanFactory(IBodyPartExtractor* bpExtractor, IBodyBuilder* bodyBuilder);
	~HangmanFactory();

	THangmanShPtr CreateFromFile(const std::string& fileName);
};

}

#endif
