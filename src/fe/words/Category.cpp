#include "fe/words/Category.h"

using namespace std;

namespace fe
{

// =============================================================================
//	CONSTANTS
// =============================================================================
const string   DEF_CATEGORY_NAME("Unnamed Category");
const Category InvalidCategory("73067B27-E101-43AF-8492-95B7F92B8D2E");

// =============================================================================
//	NON-MEMBER FUNCTIONS
// =============================================================================
bool operator==(const Category& A, const Category& B)
{
	return A.m_Name == B.m_Name;
}

bool operator!=(const Category& A, const Category& B)
{
	return A.m_Name != B.m_Name;
}

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
Category::Category(const string& name,
				   const TWordVec& words) :
	m_Name(name)
{
	srand(time(0));
	AddWords(words);
}

Category::Category(const Category& toCopy)
{
	Copy(toCopy);
}

Category& Category::operator=(const Category& toCopy)
{
	if (this == &toCopy)
		return *this;

	Copy(toCopy);
	return *this;
}

Category::~Category()
{
}

// =============================================================================
//	PRIVATE AND PROTECTED METHODS
// =============================================================================
void Category::Copy(const Category& toCopy)
{
	m_Name  	= toCopy.m_Name;
	m_Words 	= toCopy.m_Words;
	m_RandomVec = toCopy.m_RandomVec;

	GenerateRandomVector();
}

void Category::GenerateRandomVector()
{
	m_RandomVec.clear();
	
	for (UI32 i = 0; i < m_Words.size(); ++i)
		m_RandomVec.push_back(i);

	random_shuffle(m_RandomVec.begin(), m_RandomVec.end());
}

UI32 Category::GetNextRandomIndex()
{
	if (m_RandomVec.empty())
		GenerateRandomVector();

	UI32 idx = m_RandomVec.front();
	m_RandomVec.erase(m_RandomVec.begin());
	return idx;
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
bool Category::AddWord(const Word& word)
{
	if (!word.IsValid() || ContainsWord(word))
		return false;

	m_Words.push_back(word);
	return true;
}

bool Category::AddWords(const TWordVec& words)
{
	bool allok = true;
	for (auto& word : words)
		if (!AddWord(word))
			allok = false;
	return allok;
}

bool Category::RemoveWord(const Word& word)
{
	auto it = m_Words.end();
	if ((it = find(m_Words.begin(), m_Words.end(), word)) == m_Words.end())
		return false;
	m_Words.erase(it);
	return true;
}

bool Category::RemoveWords(const TWordVec& words)
{
	bool allok = true;
	for (auto& word : words)
		if (!RemoveWord(word))
			allok = false;
	return allok;
}

void Category::Clear()
{
	m_Words.clear();
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
string Category::GetName() const 			 { return m_Name; }
void   Category::SetName(const string& name) { m_Name = name; }

const TWordVec& Category::GetWords() const
{
	return m_Words;
}

Word Category::GetRandomWord()
{
	if (IsEmpty())
		return InvalidWord;

	return m_Words[GetNextRandomIndex()];
}

UI32 Category::GetWordCount() const
{
	return m_Words.size();
}

// =============================================================================
//	QUESTION METHODS
// =============================================================================
bool Category::IsValid() const
{
	return m_Name != InvalidCategory.m_Name;
}

bool Category::IsEmpty() const
{
	return m_Words.empty();
}

bool Category::ContainsWord(const Word& word) const
{
	return find(m_Words.begin(), m_Words.end(), word) != m_Words.end();
}

// =============================================================================
//	DEBUG METHODS
// =============================================================================
void Category::PrintDebug(const string& spaces) const
{
	cout << spaces << "CATEGORY" << endl;
	cout << spaces << "  Name:       \"" << m_Name << "\"" << endl;
	cout << spaces << "  Word Count: " << GetWordCount() << endl;
	cout << spaces << "  Words:" << endl;

	for (auto& word : m_Words)
	{
		word.PrintDebug(spaces + "    ");
		cout << spaces << "    --" << endl;
	}
}

}
