#include "fe/utils/FileUtils.h"

using namespace std;

namespace fe
{

// =============================================================================
//	STATIC METHODS
// =============================================================================
bool FileUtils::Exists(const string& fileName)
{
	struct stat buffer;
	return (stat(fileName.c_str(), &buffer) == 0);
}

bool FileUtils::ReadFirstLine(const string& readFrom, string& writeTo)
{
	ifstream file;

	file.open(readFrom.c_str());

	if (!file)
	{
		cerr << "ERROR: No se pudo abrir el fichero: " << readFrom << endl;
		return false;
	}

	getline(file, writeTo);
	
	file.close();
	return true;
}

bool FileUtils::ReadLines(const string& readFrom, list<string>& writeTo)
{
	ifstream file;
	string 	 readLine;

	file.open(readFrom.c_str());

	if (!file)
	{
		cerr << "ERROR: No se pudo abrir el fichero: " << readFrom << endl;
		return false;
	}

	while (!file.eof())
	{
		readLine = "";
		getline(file, readLine);

		// Ignorar lineas en blanco
		if (readLine == "")
			continue;

		writeTo.push_back(readLine);
	}

	file.close();

	return true;
}

bool FileUtils::ReadLines(const string& readFrom, string& writeTo)
{
	ifstream file;
	string 	 readLine;
	writeTo = "";

	file.open(readFrom.c_str());

	if (!file)
	{
		cerr << "ERROR: No se pudo abrir el fichero: " << readFrom << endl;
		return false;
	}

	while (!file.eof())
	{
		readLine = "";
		getline(file, readLine);

		// Ignorar lineas en blanco
		if (readLine == "")
			continue;

		writeTo += readLine;
	}

	file.close();

	return true;
}

bool FileUtils::ReadLines(const string& readFrom, list<wstring>& writeTo)
{
	wifstream file;
	wstring   readLine;

	file.open(readFrom.c_str());

	if (!file)
	{
		cerr << "ERROR: No se pudo abrir el fichero: " << readFrom << endl;
		return false;
	}

	while (!file.eof())
	{
		readLine = L"";
		file >> readLine;

		// Ignorar lineas en blanco
		if (readLine == L"")
			continue;

		writeTo.push_back(readLine);
	}

	file.close();

	return true;
}
   
bool FileUtils::ReadLines(const std::string& readFrom, std::wstring& writeTo)
{
	wifstream file;
	wstring   readLine;
	writeTo = L"";

	file.open(readFrom.c_str());

	if (!file)
	{
		cerr << "ERROR: No se pudo abrir el fichero: " << readFrom << endl;
		return false;
	}

	while (!file.eof())
	{
		readLine = L"";
		file >> readLine;

		// Ignorar lineas en blanco
		if (readLine == L"")
			continue;

		writeTo += readLine;
	}

	file.close();

	return true;
}

bool FileUtils::WriteLines(const string& writeTo, const list<string>& readFrom)
{
	ofstream writeFile;
	writeFile.open(writeTo.c_str());

	if (!writeFile)
	{
		cerr << "ERROR: No se pudo crear el fichero: " << writeTo << endl;
		return false;
	}

	StringIterator it;

	for (it = readFrom.begin(); it != readFrom.end(); ++it)
		writeFile << *it << endl;

	writeFile.close();

	return true;
}

bool FileUtils::WriteLines(const string& writeTo, const list<list<string> >& readFrom)
{
	ofstream writeFile;
	writeFile.open(writeTo.c_str());

	if (!writeFile)
	{
		cerr << "ERROR: No se pudo crear el fichero: " << writeTo << endl;
		return false;
	}

	list<list<string> >::const_iterator listIt;
	StringIterator it;

	for (listIt = readFrom.begin(); listIt != readFrom.end(); ++listIt)
		for (it = (*listIt).begin(); it != (*listIt).end(); ++it)
			writeFile << *it << endl;

	writeFile.close();

	return true;
}

}
