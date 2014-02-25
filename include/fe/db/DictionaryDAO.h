#ifndef __DICTIONARY_DAO_H__
#define __DICTIONARY_DAO_H__

#include "Kompex/KompexSQLiteDatabase.h"
#include "Kompex/KompexSQLiteStatement.h"
#include "Kompex/KompexSQLiteException.h"

#include "fe/words/Dictionary.h"

namespace fe
{

class IDictionaryDAO;

typedef std::shared_ptr<IDictionaryDAO> TIDictionaryDAOPtr;

class IDictionaryDAO
{
private:
	IDictionaryDAO(const IDictionaryDAO& toCopy);
	IDictionaryDAO& operator=(const IDictionaryDAO& toCopy);

public:
	IDictionaryDAO() 		  {}
	virtual ~IDictionaryDAO() {}

	virtual TDictionaryID InsertDictionary(const std::string& name,
										   const std::string& lang,
										   const std::string& characterSet,
								   		   const std::string& fontFile) = 0;
	virtual TDictionaryPtr GetDictionaryByID(const TDictionaryID id) = 0;
	virtual TDictionaryList GetAllDictionaries() = 0;

	virtual bool Exists(const TDictionaryID id) = 0;
	virtual bool Exists(const std::string& name) = 0;
};

class DictionaryDAO
{
private:
	static TIDictionaryDAOPtr m_DAO;

	DictionaryDAO();
	DictionaryDAO(const DictionaryDAO& toCopy);
	DictionaryDAO& operator=(const DictionaryDAO& toCopy);

public:
	virtual ~DictionaryDAO() {}

	static TDictionaryID InsertDictionary(const std::string& name,
										  const std::string& lang,
										  const std::string& characterSet,
										  const std::string& fontFile);
	static TDictionaryPtr GetDictionaryByID(const TDictionaryID id);
	static TDictionaryList GetAllDictionaries();

	static bool Exists(const TDictionaryID id);
	static bool Exists(const std::string& name);

	static void SetDAO(const TIDictionaryDAOPtr& dao);
};

}

#endif
