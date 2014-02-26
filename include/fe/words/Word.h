#ifndef __WORD_H__
#define __WORD_H__

#include <iostream>
#include <vector>

#include "fe/types/BasicTypes.h"

namespace fe
{

class Word;

typedef std::vector<Word> TWordVec;

extern const std::string DEF_WORD_STRING;
extern const std::string DEF_WORD_HINT;
extern const Word 		 InvalidWord;

class Word
{
private:
	std::string m_String;
	std::string m_Hint;

	void Copy(const Word& toCopy);

public:
	Word(const std::string& str = DEF_WORD_STRING, const std::string& hint = DEF_WORD_HINT);
	Word(const Word& toCopy);
	Word& operator=(const Word& toCopy);
	virtual ~Word();

	friend bool operator==(const Word& A, const Word& B);
	friend bool operator!=(const Word& A, const Word& B);

	const std::string& GetString() const;
	const std::string& GetHint() const;

	void SetString(const std::string& str);
	void SetHint(const std::string& hint);

	bool IsValid() const;

	void PrintDebug(const std::string& spaces = "") const;
};

bool operator==(const Word& A, const Word& B);
bool operator!=(const Word& A, const Word& B);

}

#endif
