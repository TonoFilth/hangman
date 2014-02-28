#ifndef __QUERYABLE_WORD_H__
#define __QUERYABLE_WORD_H__

#include "fe/words/Word.h"

namespace fe
{

class QWord;

typedef UI32 			   TWordID;
typedef std::vector<QWord> TQWordVec;

extern const TWordID ERR_WORD_ID;

class QWord : public Word
{
private:
	friend class WordDAO;
	
	TWordID m_ID;
	QWord(const TWordID id,
		  const std::string& str,
		  const std::string& hint);

public:
	QWord(const QWord& toCopy);
	QWord& operator=(const QWord& toCopy);
	virtual ~QWord();

	TWordID GetID() const;
};

}

#endif
