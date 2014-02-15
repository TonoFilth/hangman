#ifndef __WORD_VIEWER_H__
#define __WORD_VIEWER_H__

#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>

#include "fe/words/Word.h"
#include "fe/ui/LetterButton.h"
#include "fe/types/SpriteTypes.h"
#include "fe/types/PointerTypes.h"

namespace fe
{

class WordViewer;

typedef std::function<void(WordViewer* sender, const wchar_t letter)> TTryLetterCallback;

class WordViewer
{
private:
	Word 			   m_Word;
	TTryLetterCallback m_Callback;

	TFontPtr	  m_LetterFont;
	sf::Vector2f  m_LetterSize;
	sf::FloatRect m_LetterPadding;

	TTexturePtr m_UnderlineTexture;
	TSpriteList m_UnderlineSprites;

	TLetterButtonList m_VisibleLetterList;
	TLetterButtonList m_HiddenLetterList;

	void GenerateLetters();

	WordViewer(const WordViewer& toCopy);
	WordViewer& operator=(const WordViewer& toCopy);

public:
	WordViewer(const TFontPtr& font, const TTexturePtr& lUndTexture);
	~WordViewer();

	bool TryLetter(const wchar_t letter);
	void HideWord();
	void RevealWord();
	void Draw(sf::RenderWindow& window) const;

	UI32 GetRemainingLetters() const;

	void SetTryLetterCallback(const TTryLetterCallback& callback);
	void SetLetterUnderlineTexture(const TTexturePtr& lUndTexture);
	void SetWord(const Word& word);

	bool IsWordVisible() const;
};

}

#endif
