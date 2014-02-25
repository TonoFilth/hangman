#include "fe/utils/StringUtils.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	STATIC METHODS
// =============================================================================
UI32 StringUtils::U8Length(const string& utf8string)
{
	return utf8::distance(utf8string.begin(), utf8string.end());
}

TStringVec StringUtils::U8Split(const string& utf8string)
{
	utf8::iterator<string::const_iterator> iter(utf8string.begin(),
												utf8string.begin(),
												utf8string.end());

	TStringVec out;

	for(int i = 0; i < utf8::distance(utf8string.begin(), utf8string.end()); i++, ++iter)
	{
		string s;
		utf8::append(*iter, back_inserter(s));
		out.push_back(s);
	}

	return out;
}

TCodePointVec StringUtils::U8toU32(const string& utf8string)
{
	TCodePointVec utf32result;
	const char* source = utf8string.data();

	utf8::utf8to32(source, source + strlen(source) + 1, back_inserter(utf32result));

	return utf32result;
}

string StringUtils::U32toU8(const TCodePointVec& codepoints)
{
	string out;
	utf8::utf32to8(codepoints.begin(), codepoints.end(), back_inserter(out));
	return out;
}

String StringUtils::U8toSFML(const string& str)
{
	return String(U8toU32(str).data());
}

string StringUtils::SFMLtoU8(const String& str)
{
	string out;
	utf8::utf32to8(str.begin(), str.end(), back_inserter(out));
	return out;
}

bool StringUtils::IsU8(const string& str)
{
	return utf8::is_valid(str.begin(), str.end());
}

string StringUtils::ToLower(const string& str)
{
	string s(str);
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	return s;
}

string StringUtils::ToUpper(const string& str)
{
	string s(str);
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	return s;
}

void StringUtils::FindAndReplace(string& str, const string& find, const string& replace)
{
	for (string::size_type i = 0; (i = str.find(find, i)) != string::npos;)
    {
        str.replace(i, find.length(), replace);
        i += (replace.length() > 0 ? replace.length() : 1) - find.length() + 1;
    }
}

void StringUtils::FindAnyAndReplace(string& str, const string& find, const string& replace)
{
	for (string::size_type i = str.find_first_of(find, 0); i != string::npos;)
    {
        str.replace(i, 1, replace);
        i = str.find_first_of(find, i + 2);
    }
}

void StringUtils::Translate(string& str, const TStringVec& charsToTranslate, const TStringVec& translatedChars)
{
	if (charsToTranslate.size() != translatedChars.size())
	{
		cerr << "Translation vector lengths must agree" << endl;
		return;
	}

	for (UI32 i = 0; i < charsToTranslate.size(); ++i)
		FindAndReplace(str, charsToTranslate[i], translatedChars[i]);
}

}
