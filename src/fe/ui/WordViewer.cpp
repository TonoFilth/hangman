#include "fe/ui/WordViewer.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
WordViewer::WordViewer(const UI32 width, const UI32 height, const TFontPtr& font,
	const TTexturePtr& lUndTexture) :
	m_Word(InvalidWord),
	m_Size(width, height),
	m_Position(0, 0),
	m_Callback(nullptr),
	m_LetterFont(font),
	m_LetterSize(0, 0),
	m_LetterPadding(5, 0, 5, 0),
	m_UnderlineMargin(5),
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

	auto letterCount = StringUtils::U8Length(m_Word.GetString());
	auto txSize = m_UnderlineTexture->getSize();

	Vector2f drawableArea(
		m_Size.x - (m_LetterPadding.left + m_LetterPadding.width) * letterCount,
		m_Size.y - txSize.y - m_UnderlineMargin - m_LetterPadding.top - m_LetterPadding.height);

	m_LetterSize.x = drawableArea.x / static_cast<F32>(letterCount);
	m_LetterSize.y = drawableArea.y;

	Vector2f curPos(m_LetterPadding.left + m_Position.x,
					m_LetterPadding.top  + m_Position.y);

	// Get the UTF-8 individual codepoints to iterate over them
	auto utf8letters = StringUtils::U8Split(m_Word.GetString());

	for (UI32 i = 0; i < letterCount; ++i)
	{
		if (utf8letters[i] == " ")
		{
			curPos.x += m_LetterSize.x + m_LetterPadding.left + m_LetterPadding.width;
			continue;
		}

		Sprite undSprite(*m_UnderlineTexture);
		LetterButton letter(utf8letters[i], m_LetterFont, m_LetterSize);

		letter.SetPosition(curPos);
		letter.SetLetterColor(Color::Black);
		letter.SetButtonColor(Color(0, 0, 0, 0));

		undSprite.setPosition(curPos.x,
			curPos.y + m_LetterSize.y + m_LetterPadding.top + m_LetterPadding.height + m_UnderlineMargin);

		auto txSize = m_UnderlineTexture->getSize();

		// Adjust the underline sprite's width
		if (txSize.x != m_LetterSize.x)
		{
			auto scale = m_LetterSize.x / static_cast<F32>(txSize.x);
			undSprite.setScale(scale, 1.0);
		}

		m_HiddenLetterList.push_back(letter);
		m_UnderlineSprites.push_back(undSprite);

		curPos.x += m_LetterSize.x + m_LetterPadding.left + m_LetterPadding.width;
	}
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
bool WordViewer::TryLetter(const std::string& letter)
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
