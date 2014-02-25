#ifndef __WORD_H__
#define __WORD_H__

#include <iostream>
#include <vector>

#include "fe/types/BasicTypes.h"

namespace fe
{

class Word;
class WordDAOSqlite;

typedef UI32			  TWordID;
typedef std::vector<Word> TWordVec;

extern const std::string DEF_WORD_STRING;
extern const std::string DEF_WORD_HINT;
extern const TWordID ERR_WORD_ID;
extern const Word InvalidWord;

class Word
{
private:
	friend class WordDAOSqlite;
	static TWordID WORD_ID;

	TWordID	 	m_ID;
	std::string m_String;
	std::string m_Hint;

	void Copy(const Word& toCopy);

public:
	Word(const std::string& str = DEF_WORD_STRING, const std::string& hint = DEF_WORD_HINT);
	Word(const Word& toCopy);
	Word& operator=(const Word& toCopy);
	virtual ~Word();

	friend bool operator==(const Word& wordA, const Word& wordB);
	friend bool operator!=(const Word& wordA, const Word& wordB);

	TWordID GetID() const;
	const std::string& GetString() const;
	const std::string& GetHint() const;

	void SetString(const std::string& str);
	void SetHint(const std::string& hint);

	bool IsValid() const;

	void PrintDebug(const std::string& spaces = "") const;
};

bool operator==(const Word& wordA, const Word& wordB);
bool operator!=(const Word& wordA, const Word& wordB);

}

#endif
