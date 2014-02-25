#ifndef __WORD_VIEWER_H__
#define __WORD_VIEWER_H__

#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>

#include "fe/words/Word.h"
#include "fe/ui/LetterButton.h"
#include "fe/types/SpriteTypes.h"
#include "fe/types/PointerTypes.h"
#include "fe/utils/StringUtils.h"

namespace fe
{

class WordViewer;

typedef std::function<void(WordViewer*, const std::string&)> TTryLetterCallback;

class WordViewer
{
private:
	Word 			   m_Word;
	sf::Vector2f 	   m_Size;
	sf::Vector2f	   m_Position;
	TTryLetterCallback m_Callback;

	TFontPtr	  m_LetterFont;
	sf::Vector2f  m_LetterSize;
	sf::FloatRect m_LetterPadding;
	F32			  m_UnderlineMargin;

	TTexturePtr m_UnderlineTexture;
	TSpriteList m_UnderlineSprites;

	TLetterButtonList m_VisibleLetterList;
	TLetterButtonList m_HiddenLetterList;

	void GenerateLetters();

	WordViewer(const WordViewer& toCopy);
	WordViewer& operator=(const WordViewer& toCopy);

public:
	WordViewer(const UI32 width, const UI32 height, const TFontPtr& font,
			   const TTexturePtr& lUndTexture);
	~WordViewer();

	bool TryLetter(const std::string& letter);
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
