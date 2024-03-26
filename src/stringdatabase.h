/* Validates SDB file and initializes Database object for container entries  */
#include <BinaryIO.h>
#include <fstream>
#pragma once

using namespace std;
using namespace BinaryIO;

struct StGameString {
	uint32_t address;
	uint32_t size;
	uint32_t guid;
	std::string string;
};

class CStringDatabase 
{
	enum enHeaderTags {
		SDB_NO_MANGLING = 0x0,
		SDB_MANGLED = 0x100,
	};

public:
	CStringDatabase(const char* filePath);

public:
	void save(const bool useMangledBuffer = false, const std::string savePath="");
	void load();
	bool isMangled() { return m_tag == SDB_MANGLED; }

private:
	std::string getString(const uint32_t& size, const uint32_t& address);
	void demangleString(std::string& target, const uint32_t& address);
	void mangleString(std::string& target, const uint32_t& address);

private:
	void readContents();
	void validateContainer();
	void writeDatabase(const bool& useMangleBuffer, std::ofstream& outFile);
	void sortDatabase();

private:
	std::vector<StGameString> m_strings;
	std::ifstream* m_fileStream;
	std::string m_filePath;
	uint32_t m_tag;
	bool isOk = false;
};