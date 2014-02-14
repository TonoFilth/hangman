#ifndef __WORD_H__
#define __WORD_H__

#include <vector>
#include <SFML/Graphics.hpp>

namespace fe
{

class Word;

typedef std::vector<Word> TWordVec;

class Word
{
private:
	sf::String m_Word;
	sf::String m_Hint;

	void Copy(const Word& toCopy);

public:
	Word();
	Word(const sf::String& word, const sf::String& hint);
	Word(const Word& toCopy);
	Word& operator=(const Word& toCopy);
	~Word();

	const sf::String& GetWord() const;
	const sf::String& GetHint() const;
	void SetWord(const sf::String& word);
	void SetHint(const sf::String& hint);
};

}

#endif
