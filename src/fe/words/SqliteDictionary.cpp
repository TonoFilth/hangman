#include "fe/words/SqliteDictionary.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTANTS
// =============================================================================
const UI32 MAX_LOADED_CATEGORIES = 2;

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
SqliteDictionary::SqliteDictionary(const TDictionaryID id,
								   const string& name,
								   const string& lang,
								   const string& characterSet,
					 			   const string& fontFile,
								   const TCategoryList& categoryList) :
	RandomDictionary(name, lang, characterSet, fontFile, categoryList),
	m_ID(id)
{
	//m_Database = make_shared<SQLiteDatabase>(databaseFile, SQLITE_OPEN_READONLY, nullptr);
	LoadCategories();
}

SqliteDictionary::~SqliteDictionary()
{
}

// =============================================================================
//	PRIVATE AND PROTECTED METHODS
// =============================================================================
void SqliteDictionary::LoadCategories()
{
	auto categories = CategoryDAO::GetCategoriesByDictionaryID(m_ID);

	for (auto& category : categories)
	{
		auto words = WordDAO::GetWordsByCategoryID(category.id);
		RandomDictionary::AddCategory(category);
		
		for (auto& word : words)
		{
			RandomDictionary::AddWord(word, category.id);
			cout << "Loaded word: " << word.GetWord() << endl;
		}
	}
}

bool SqliteDictionary::LoadCategory(const TCategoryID categoryID)
{
	return false;
}

void SqliteDictionary::LoadWords(const TCategoryID categoryID)
{
}

// =============================================================================
//	VIRTUAL METHODS
// =============================================================================
Word SqliteDictionary::GetWord(const TCategoryID categoryID, const UI32 index)
{
	if (categoryID == AnyCategory.id)
		return RandomDictionary::GetWord(categoryID, index);

	if (!ContainsCategory(categoryID))
	{
		if (GetCategoryCount() >= MAX_LOADED_CATEGORIES)
			RandomDictionary::RemoveCategory(RandomDictionary::GetCategoryList().front().id);

		if (!LoadCategory(categoryID))
			return InvalidWord;
	}

	return RandomDictionary::GetWord(categoryID, index);
}

bool SqliteDictionary::AddWord(const Word& word, const TCategoryID categoryID)
{
	cerr << "SqliteDictionary doesn't allow addition of words" << endl;
	return true;
}

TCategoryID SqliteDictionary::AddCategory(const string& categoryName)
{
	cerr << "SqliteDictionary doesn't allow addition of categories" << endl;
	return false;
}

bool SqliteDictionary::RemoveWord(const Word& word)
{
	cerr << "SqliteDictionary doesn't allow removal of words" << endl;
	return false;
}

bool SqliteDictionary::RemoveCategory(const TCategoryID categoryID)
{
	cerr << "SqliteDictionary doesn't allow removal of categories" << endl;
	return false;
}

}
