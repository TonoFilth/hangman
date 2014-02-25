#include "fe/words/Category.h"

using namespace std;

namespace fe
{

// =============================================================================
//	CONSTANTS
// =============================================================================
const string DEF_CATEGORY_NAME("Unnamed Category");
const TCategoryID ERR_CATEGORY_ID(0);
const Category InvalidCategory("73067B27-E101-43AF-8492-95B7F92B8D2E");

// =============================================================================
//	STATIC FIELDS
// =============================================================================
TCategoryID Category::CATEGORY_ID = 0;

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
Category::Category(const string& name) :
	Category(name, TWordVec())
{
}

Category::Category(const string& name, const TWordVec& words) :
	m_ID(CATEGORY_ID++),
	m_Name(name),
	m_Words(words)
{
	srand(time(0));
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
	//m_ID    = CATEGORY_ID++;
	m_ID	= toCopy.m_ID;
	m_Name  = toCopy.m_Name;
	m_Words = toCopy.m_Words;
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
void Category::AddWord(const Word& word)
{
	if (ContainsWord(word))
		return;

	m_Words.push_back(word);
}

void Category::AddWords(const TWordVec& words)
{
	for (auto& word : words)
		AddWord(word);
}

void Category::RemoveWord(const TWordID& id)
{
	auto word = GetWord(id);

	if (!word.IsValid())
		return;

	RemoveWord(word);
}

void Category::RemoveWord(const Word& word)
{
	auto it = m_Words.begin();

	if ((it = find(m_Words.begin(), m_Words.end(), word)) == m_Words.end())
		return;

	m_Words.erase(it);
}

void Category::RemoveWords(const TWordVec& words)
{
	auto it = m_Words.begin();

	while (it != m_Words.end())
		if ((it = find_first_of(m_Words.begin(), m_Words.end(), words.begin(), words.end())) != m_Words.end())
			m_Words.erase(it);
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
TCategoryID Category::GetID() const
{
	return m_ID;
}

string Category::GetName() const
{
	return m_Name;
}

Word Category::GetWord(const TWordID& id) const
{
	auto it = m_Words.begin();

	if ((it = find_if(m_Words.begin(), m_Words.end(),
		[id] (const Word& w) { return w.GetID() == id; })) == m_Words.end())
		return InvalidWord;

	return *it;
}

Word Category::GetRandomWord() const
{
	if (IsEmpty())
		return InvalidWord;

	UI32 range = m_Words.size() - 1;
	UI32 index = UI32((range * rand()) / (RAND_MAX + 1.0));

	return m_Words[index];
}

UI32 Category::GetWordCount() const
{
	return m_Words.size();
}

void Category::SetName(const string& name)
{
	m_Name = name;
}

// =============================================================================
//	QUESTION METHODS
// =============================================================================
bool Category::ContainsWord(const Word& word) const
{
	return (find(m_Words.begin(), m_Words.end(), word) != m_Words.end());
}

bool Category::IsValid() const
{
	return m_ID   != ERR_CATEGORY_ID ||
		   m_Name != InvalidCategory.m_Name;
}

bool Category::IsEmpty() const
{
	return m_Words.empty();
}

// =============================================================================
//	DEBUG METHODS
// =============================================================================
void Category::PrintDebug(const string& spaces) const
{
	cout << spaces << "CATEGORY" << endl;
	cout << spaces << "  ID:         " << m_ID << endl;
	cout << spaces << "  Name:       \"" << m_Name << "\"" << endl;
	cout << spaces << "  Word Count: " << GetWordCount() << endl;
	cout << spaces << "  Words:" << endl;

	for (auto& word : m_Words)
	{
		word.PrintDebug(spaces + "  ");
		cout << spaces << "  --" << endl;
	}
}

}
