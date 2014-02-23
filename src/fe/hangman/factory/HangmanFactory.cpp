#include "fe/hangman/factory/HangmanFactory.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
HangmanFactory::HangmanFactory(const TBodyPartExtractorPtr& bpExtractor,
							   const TBodyBuilderPtr& bodyBuilder) :
	m_BodyBuilder(bodyBuilder),
	m_BodyPartExtractor(bpExtractor)
{
	if (m_BodyBuilder == nullptr || m_BodyPartExtractor == nullptr)
		throw;
}

HangmanFactory::~HangmanFactory()
{
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
THangmanShPtr HangmanFactory::Create()
{
	string 		 txFileName;
	TBodyPartVec bodyParts;

	THangmanShPtr hangman(new Hangman());

	// Extract body parts
	if (!m_BodyPartExtractor->Extract(txFileName, bodyParts))
	{
		cerr << "Can't extract body parts" << endl;
		return nullptr;
	}

	// Verify that all body parts are OK
	if (!BodyPartChecker::Check(bodyParts))
	{
		cerr << "Malformed body parts. Hangman creation canceled" << endl;
		return nullptr;
	}

	// Load hangman texture
	if (!hangman->m_Texture.loadFromFile(txFileName))
	{
		cerr << "Can't load hangman texture " << txFileName << endl;
		return nullptr;
	}

	hangman->m_Texture.setSmooth(true);

	// Build the hangman sprite
	if (!m_BodyBuilder->Build(bodyParts, hangman->m_Texture, hangman->m_Hangman))
	{
		cerr << "Can't build hangman body from the supplied body parts" << endl;
		return nullptr;
	}

	return hangman;
}

}
