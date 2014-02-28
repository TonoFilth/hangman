#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__

#include <list>
#include <vector>
#include <cctype>
#include <string>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <SFML/System.hpp>

#include "utf8cpp/utf8.h"
#include "fe/types/BasicTypes.h"

namespace fe
{

typedef std::vector<UI32>		 TCodePointVec;
typedef std::vector<std::string> TStringVec;

class StringUtils
{
private:
	StringUtils();
	StringUtils(const StringUtils& toCopy);
	StringUtils& operator=(const StringUtils& toCopy);
	~StringUtils();

public:
	// UTF encodings
	static UI32 U8Length(const std::string& utf8string);
	static TStringVec U8Split(const std::string& utf8string);

	static TCodePointVec U8toU32(const std::string& utf8string);
	static std::string U32toU8(const TCodePointVec& codepoints);

	static sf::String U8toSFML(const std::string& str);
	static std::string SFMLtoU8(const sf::String& str);

	static bool IsU8(const std::string& str);

	// General functions
	static std::string ToLower(const std::string& str);
	static std::string ToUpper(const std::string& str);

	static void FindAndReplace(std::string& str, const std::string& find, const std::string& replace);
	static void FindAnyAndReplace(std::string& str, const std::string& find, const std::string& replace);
	static void Translate(std::string& str, const TStringVec& charsToTranslate, const TStringVec& translatedChars);
	static TStringVec Explode(const std::string& str, const std::string& delimiter);
	static TStringVec ExplodeOmitQuotes(const std::string& str, const std::string& delimiter);
};

}

#endif
