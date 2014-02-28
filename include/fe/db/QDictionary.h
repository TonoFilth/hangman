#ifndef __QUERYABLE_DICTIONARY_H__
#define __QUERYABLE_DICTIONARY_H__

#include "fe/words/Dictionary.h"

namespace fe
{

class QDictionary;

typedef UI32 					 TDictionaryID;
typedef std::vector<QDictionary> TQDictionaryVec;

extern const TDictionaryID ERR_DICTIONARY_ID;

class QDictionary : public Dictionary
{
private:
	friend class DictionaryDAO;

	TDictionaryID m_ID;

	QDictionary(const TDictionaryID id,
				const std::string& name,
				const std::string& lang,
				const std::string& cset,
				const std::string& font);
public:
	QDictionary(const QDictionary& toCopy);
	QDictionary& operator=(const QDictionary& toCopy);
	virtual ~QDictionary();

	TDictionaryID GetID() const;
};

}

#endif
