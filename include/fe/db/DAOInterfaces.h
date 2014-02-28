#ifndef __DAO_INTERFACES_H__
#define __DAO_INTERFACES_H__

#include "fe/db/QWord.h"
#include "fe/db/QCategory.h"
#include "fe/db/QDictionary.h"

namespace fe
{

class WordDAO;
class CategoryDAO;
class DictionaryDAO;

typedef std::shared_ptr<WordDAO> 	   TWordDAOPtr;
typedef std::shared_ptr<CategoryDAO>   TCategoryDAOPtr;
typedef std::shared_ptr<DictionaryDAO> TDictionaryDAOPtr;

typedef std::function<bool(const QWord&)> 		TQWordPredicate;
typedef std::function<bool(const QCategory&)> 	TQCategoryPredicate;
typedef std::function<bool(const QDictionary&)> TQDictionaryPredicate;

/* \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// /////////////////////////////////////////////////////////////////////////////
// 									MASTER DAO
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// ///////////////////////////////////////////////////////////////////////////*/
class MasterDAO
{
public:
	static TWordDAOPtr 	  	 Words;
	static TCategoryDAOPtr   Categories;
	static TDictionaryDAOPtr Dictionaries;
};

/* \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// /////////////////////////////////////////////////////////////////////////////
// 									WORD DAO
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// ///////////////////////////////////////////////////////////////////////////*/
class WordDAO
{
protected:
	const QWord InvalidQWord = QWord(ERR_WORD_ID,
							   		 InvalidWord.GetString(),
							   		 InvalidWord.GetHint());

	QWord CreateQWord(const TWordID id,
					  const std::string& str,
					  const std::string& hint)
	{
		return QWord(id, str, hint);
	}

public:
	virtual ~WordDAO() {}

	virtual QWord Create(const TCategoryID catID,
						 const std::string& str,
						 const std::string& hint) = 0;
	virtual bool  Update(const QWord& word) 	  = 0;
	virtual bool  Delete(const TWordID id)  	  = 0;

	virtual TQWordVec GetAll() = 0;
	virtual TQWordVec GetAllByCategory(const TCategoryID catID) = 0;
	virtual TQWordVec GetIf(const TQWordPredicate& predicate) = 0;

	virtual bool Exists(const TWordID id) = 0;
	virtual bool Exists(const std::string& word) = 0;
};

/* \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// /////////////////////////////////////////////////////////////////////////////
// 								CATEGORY DAO
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// ///////////////////////////////////////////////////////////////////////////*/
class CategoryDAO
{
protected:
	const QCategory InvalidQCategory = QCategory(ERR_CATEGORY_ID,
												 InvalidCategory.GetName());

	QCategory CreateQCategory(const TCategoryID id,
							  const std::string& name)
	{
		QCategory qc(id, name);
		auto words = MasterDAO::Words->GetAllByCategory(id);
		for (auto& word : words)
			qc.AddWord(word);
		return qc;
	}

public:
	virtual ~CategoryDAO() {}

	virtual QCategory Create(const std::string& name,
							 const TDictionaryID dicID) = 0;
	virtual bool	  Update(const QCategory& category) = 0;
	virtual bool 	  Delete(const TCategoryID id) 		= 0;

	virtual QCategory GetByID(const TCategoryID catID) 	 = 0;
	virtual QCategory GetByName(const std::string& name) = 0;

	virtual TQCategoryVec GetAll()										= 0;
	virtual TQCategoryVec GetAllByDictionary(const TDictionaryID dicID) = 0;
	virtual TQCategoryVec GetIf(const TQCategoryPredicate& predicate)   = 0;

	virtual bool Exists(const TCategoryID id) 	 = 0;
	virtual bool Exists(const std::string& name) = 0;
};

/* \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// /////////////////////////////////////////////////////////////////////////////
// 								DICTIONARY DAO
// \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
// ///////////////////////////////////////////////////////////////////////////*/
#include <iostream>
using namespace std;
class DictionaryDAO
{
protected:
	const QDictionary InvalidQDictionary = QDictionary(ERR_DICTIONARY_ID,
													   InvalidDictionary.GetName(),
													   InvalidDictionary.GetLanguage(),
													   InvalidDictionary.GetCharacterSet(),
													   InvalidDictionary.GetFont());

	QDictionary CreateQDictionary(const TDictionaryID id,
								  const std::string& name,
								  const std::string& lang,
								  const std::string& cset,
								  const std::string& font)
	{
		QDictionary qd(id, name, lang, cset, font);
		auto categories = MasterDAO::Categories->GetAllByDictionary(id);
		for (auto& category : categories)
			qd.AddCategory(category);
		return qd;
	}

public:
	virtual ~DictionaryDAO() {}

	virtual QDictionary Create(const std::string& name,
							   const std::string& lang,
							   const std::string& cset,
							   const std::string& font) = 0;
	virtual bool Update(const QDictionary& dictionary)  = 0;
	virtual bool Delete(const TDictionaryID dicID) 		= 0;

	virtual QDictionary GetByID(const TDictionaryID dicID) = 0;
	virtual QDictionary GetByName(const std::string& name) = 0;

	virtual TQDictionaryVec GetAll() 						   			  = 0;
	virtual TQDictionaryVec GetIf(const TQDictionaryPredicate& predicate) = 0;

	virtual bool Exists(const TDictionaryID id)  = 0;
	virtual bool Exists(const std::string& name) = 0;
};

}

#endif
