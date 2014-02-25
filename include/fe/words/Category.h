#ifndef __CATEGORY_H__
#define __CATEGORY_H__

#include <map>
#include <algorithm>
#include <cstdlib>
#include <time.h>

#include "fe/words/Word.h"

namespace fe
{

class Category;
class CategoryDAOSqlite;

typedef UI32 							TCategoryID;
typedef std::vector<Category>			TCategoryVec;
typedef std::map<TCategoryID, Category> TCategoryMap;

extern const std::string DEF_CATEGORY_NAME;
extern const TCategoryID ERR_CATEGORY_ID;
extern const Category InvalidCategory;

class Category
{
private:
	friend class CategoryDAOSqlite;
	static TCategoryID CATEGORY_ID;

	TCategoryID m_ID;
	std::string m_Name;
	TWordVec	m_Words;

	void Copy(const Category& toCopy);

public:
	Category(const std::string& name = DEF_CATEGORY_NAME);
	Category(const std::string& name, const TWordVec& words);
	Category(const Category& toCopy);
	Category& operator=(const Category& toCopy);
	virtual ~Category();

	void AddWord(const Word& word);
	void AddWords(const TWordVec& words);

	void RemoveWord(const TWordID& id);
	void RemoveWord(const Word& word);
	void RemoveWords(const TWordVec& words);

	TCategoryID GetID() const;
	std::string GetName() const;
	Word GetWord(const TWordID& id) const;
	Word GetRandomWord() const;
	UI32 GetWordCount() const;

	void SetName(const std::string& name);

	bool IsEmpty() const;
	bool IsValid() const;
	bool ContainsWord(const Word& word) const;

	void PrintDebug(const std::string& spaces = "") const;
};

}

#endif
