#include "fe/ui/WordViewer.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
WordViewer::WordViewer(const TFontPtr& font, const TTexturePtr& lUndTexture) :
	m_Word("undefined"),
	m_Callback(nullptr),
	m_LetterFont(font),
	m_LetterSize(30, 30),
	m_LetterPadding(0, 0, 10, 0),
	m_UnderlineTexture(lUndTexture)
{
}

WordViewer::~WordViewer()
{
}

// =============================================================================
//	PRIVATE AND PROTECTED METHODS
// =============================================================================
void WordViewer::GenerateLetters()
{
	m_UnderlineSprites.clear();

	auto letterCount = m_Word.GetWord().getSize();
	auto word = m_Word.GetWord();

	Vector2f curPos(m_LetterPadding.left, m_LetterPadding.top + 220);

	for (UI32 i = 0; i < letterCount; ++i)
	{
		if (word[i] == L' ')
		{
			curPos.x += m_LetterSize.x + m_LetterPadding.width;
			continue;
		}

		Sprite undSprite(*m_UnderlineTexture);
		LetterButton letter(word[i], *m_LetterFont, m_LetterSize);

		letter.SetPosition(curPos);
		undSprite.setPosition(curPos.x,
			curPos.y + m_LetterSize.y + m_LetterPadding.top + m_LetterPadding.height + 5);

		auto txSize = m_UnderlineTexture->getSize();

		// Adjust the underline sprite's width
		if (txSize.x != m_LetterSize.x)
		{
			auto scale = m_LetterSize.x / static_cast<F32>(txSize.x);
			undSprite.setScale(scale, 1.0);
		}

		m_HiddenLetterList.push_back(letter);
		m_UnderlineSprites.push_back(undSprite);

		curPos.x += m_LetterSize.x + m_LetterPadding.width;
	}
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
bool WordViewer::TryLetter(const wchar_t letter)
{
	list<TLetterButtonList::iterator> toErase;

	for (auto it = m_HiddenLetterList.begin(); it != m_HiddenLetterList.end(); ++it)
	{
		if (it->GetLetter() == letter)
		{
			toErase.push_back(it);
			m_VisibleLetterList.push_back(*it);
		}
	}

	if (toErase.empty())
		return false;

	for (auto& letter : toErase)
		m_HiddenLetterList.erase(letter);

	return true;
}

void WordViewer::HideWord()
{
	for (auto& visible : m_VisibleLetterList)
		m_HiddenLetterList.push_back(visible);

	m_VisibleLetterList.clear();
}

void WordViewer::RevealWord()
{
	for (auto& hidden : m_HiddenLetterList)
		m_VisibleLetterList.push_back(hidden);

	m_HiddenLetterList.clear();
}

void WordViewer::Draw(RenderWindow& window) const
{
	for (auto& underline : m_UnderlineSprites)
		window.draw(underline);

	for (auto& letter : m_VisibleLetterList)
		letter.Draw(window);
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
UI32 WordViewer::GetRemainingLetters() const
{
	return m_HiddenLetterList.size();
}

void WordViewer::SetWord(const Word& word)
{
	m_Word = word;

	m_VisibleLetterList.clear();
	m_HiddenLetterList.clear();

	GenerateLetters();
}

// =============================================================================
//	QUESTION METHODS
// =============================================================================
bool WordViewer::IsWordVisible() const
{
	return m_HiddenLetterList.empty();
}

}
