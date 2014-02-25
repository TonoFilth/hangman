#ifndef __WORD_DAO_H__
#define __WORD_DAO_H__

#include "fe/db/CategoryDAO.h"

namespace fe
{

class IWordDAO;

typedef std::shared_ptr<IWordDAO> TIWordDAOPtr;

class IWordDAO
{
private:
	IWordDAO(const IWordDAO& toCopy);
	IWordDAO& operator=(const IWordDAO& toCopy);

public:
	IWordDAO() 		    {}
	virtual ~IWordDAO() {}

	virtual bool InsertWord(const TCategoryID categoryID, const Word& word) = 0;
	virtual TWordVec GetWordsByCategoryID(const TCategoryID categoryID) = 0;
};

class WordDAO
{
private:
	static TIWordDAOPtr m_DAO;

	WordDAO();
	WordDAO(const WordDAO& toCopy);
	WordDAO& operator=(const WordDAO& toCopy);

public:
	virtual ~WordDAO() {}

	static bool InsertWord(const TCategoryID categoryID, const Word& word);
	static TWordVec GetWordsByCategoryID(const TCategoryID categoryID);

	static void SetDAO(const TIWordDAOPtr& dao);
};

}

#endif
