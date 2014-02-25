#ifndef __WORD_H__
#define __WORD_H__

#include <vector>
#include <SFML/Graphics.hpp>

namespace fe
{

class Word;

extern const Word InvalidWord;

typedef std::vector<Word> TWordVec;

class Word
{
private:
	std::string m_Word;
	std::string m_Hint;

	void Copy(const Word& toCopy);

public:
	Word();
	Word(const std::string& word, const std::string& hint = std::string(u8""));
	Word(const Word& toCopy);
	Word& operator=(const Word& toCopy);
	~Word();

	friend bool operator==(const Word& wordA, const Word& wordB);
	friend bool operator!=(const Word& wordA, const Word& wordB);

	const std::string& GetWord() const;
	const std::string& GetHint() const;
	void SetWord(const std::string& word);
	void SetHint(const std::string& hint);

	bool IsValid() const;
};

bool operator==(const Word& wordA, const Word& wordB);
bool operator!=(const Word& wordA, const Word& wordB);

}

#endif
