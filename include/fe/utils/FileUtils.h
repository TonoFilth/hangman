#ifndef __FILE_UTILS_H__
#define __FILE_UTILS_H__

#include <iostream>
#include <fstream>
#include <list>
#include <sys/stat.h>
#include <cstdlib>

namespace fe
{

typedef std::list<std::string>::const_iterator StringIterator;

class FileUtils
{
private:
	FileUtils();
	FileUtils(const FileUtils& toCopy);
	FileUtils& operator=(const FileUtils& toCopy);
	~FileUtils();

public:
    static bool Exists(const std::string& fileName);
    static bool ReadFirstLine(const std::string& readFrom, std::string& writeTo);
    static bool ReadLines(const std::string& readFrom, std::list<std::string>& writeTo);
    static bool ReadLines(const std::string& readFrom, std::string& writeTo);
    static bool WriteLines(const std::string& writeTo, const std::list<std::string>& readFrom);
    static bool WriteLines(const std::string& writeTo, const std::list<std::list<std::string> >& readFrom);
};

}

#endif
