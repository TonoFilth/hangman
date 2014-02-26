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

typedef std::vector<Category>			TCategoryVec;
typedef std::map<std::string, Category> TCategoryMap;
typedef std::vector<UI32>				TRandomIndexVec;

extern const std::string DEF_CATEGORY_NAME;
extern const Category 	 InvalidCategory;

class Category
{
private:
	std::string 	m_Name;
	TWordVec		m_Words;
	TRandomIndexVec m_RandomVec;

	void Copy(const Category& toCopy);
	void GenerateRandomVector();
	UI32 GetNextRandomIndex();

public:
	Category(const std::string& name = DEF_CATEGORY_NAME, const TWordVec& words = TWordVec());
	Category(const Category& toCopy);
	Category& operator=(const Category& toCopy);
	virtual ~Category();

	friend bool operator==(const Category& A, const Category& B);
	friend bool operator!=(const Category& A, const Category& B);

	bool AddWord(const Word& word);
	bool AddWords(const TWordVec& words);

	bool RemoveWord(const Word& word);
	bool RemoveWords(const TWordVec& words);

	void Clear();

	std::string GetName() const;
	void SetName(const std::string& name);

	const TWordVec& GetWords() const;
	Word GetRandomWord();
	UI32 GetWordCount() const;

	bool IsEmpty() const;
	bool IsValid() const;
	bool ContainsWord(const Word& word) const;

	void PrintDebug(const std::string& spaces = "") const;
};

bool operator==(const Category& A, const Category& B);
bool operator!=(const Category& A, const Category& B);

}

#endif
