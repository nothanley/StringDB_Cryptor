#include "stringdatabase.h"
#include "winsock.h"
#include <iostream>
#include <algorithm>

using namespace std;
using namespace BinaryIO;

CStringDatabase::CStringDatabase(const char* path) :
	m_filePath(path),
	m_fileStream(nullptr),
	m_tag(0){}

void
CStringDatabase::load() 
{
	/* Verify file can be read and is accessible */
	m_fileStream = new std::ifstream(m_filePath, ios::binary);
	if (!m_fileStream->good()) {
		printf("Could not read SDB file.\n");
		return; }

	/* Verify header tag is a known value */
	CStringDatabase::validateContainer();

	if (!this->isOk) {
		printf("Could not parse unknown SDB format.\n");
		return;}

	/* Parse all strigtable contents */
	CStringDatabase::readContents();
	m_fileStream->close();
	printf("Database load complete.\n");
}

void
CStringDatabase::demangleString(std::string& target, const uint32_t& address)
{
	uint8_t key = (address & 0xFF) ^ 0xCD;

	for (char& character : target) 
	{
		/* XOR string character with current key */
		uint8_t saveChar = character;
		character ^= key;

		/* Update the key value with original character value */
		key = saveChar;
	}
}

void
CStringDatabase::mangleString(std::string& target, const uint32_t& address)
{
	uint8_t key = (address & 0xFF) ^ 0xCD;

	for (char& character : target)
	{
		/* XOR string character with current key */
		uint8_t saveChar = character;
		character ^= key;

		/* Update the key value and XOR with original char value */
		key ^= saveChar;
	}
}

std::string
CStringDatabase::getString(const uint32_t& size, const uint32_t& address) 
{
	/* Seek to string entry */
	m_fileStream->seekg(address);

	/* get string entry and demangle if specified in header tag */
	std::string sdbString;
	sdbString.resize(size);
	m_fileStream->read(&sdbString[0], size);

	if (m_tag == SDB_MANGLED)
		demangleString(sdbString, address);

	return sdbString;
}

void
CStringDatabase::readContents()
{
	printf("Opening File: %s\n", m_filePath.c_str());
	uint32_t numStrings = ReadUInt32(*m_fileStream);
	uintptr_t entryAddress = m_fileStream->tellg();

	/* iterates through each sdb entry and append to vector */
	for (int i = 0; i < numStrings; i++)
	{
		m_fileStream->seekg( entryAddress + (i*0xC) );

		StGameString sdbEntry;
		sdbEntry.address = ReadUInt32(*m_fileStream);
		sdbEntry.size	 = ReadUInt32(*m_fileStream);
		sdbEntry.guid  	 = ReadUInt32(*m_fileStream);
		sdbEntry.string  = CStringDatabase::getString(sdbEntry.size, sdbEntry.address);

		m_strings.push_back(sdbEntry);
	}
}

void
CStringDatabase::validateContainer() {
	m_fileStream->seekg(ios::beg);
	m_tag = ReadUInt32(*m_fileStream);

	// Check header tag with known values
	if (m_tag == SDB_MANGLED || m_tag == SDB_NO_MANGLING)
		this->isOk = true;
}

void
CStringDatabase::save(const bool useMangledBuffer, const std::string saveFile)
{
	std::string savePath = (saveFile == "") ? m_filePath : saveFile;
	uint32_t numStrings = this->m_strings.size();

	if (numStrings == 0) {
		printf("Cannot save empty database.\n");
		return;
	}

	std::ofstream outFile(savePath, std::ios::binary);
	if (!outFile.is_open()) {
		std::cerr << "Error opening the file " << savePath << " for writing." << std::endl;
	}

	this->sortDatabase();
	writeDatabase(useMangledBuffer, outFile);
	
	printf("Database save complete.\n");
}

void
CStringDatabase::sortDatabase() {
	// Sorts database strings based on the guid member
	std::sort(m_strings.begin(), m_strings.end(),
		[](const StGameString& a, const StGameString& b) {return a.guid < b.guid;});
}

void
CStringDatabase::writeDatabase(const bool& useMangleBuffer, std::ofstream& outFile)
{
	/* Initialize file and string buffers */
	uint32_t numStrings = this->m_strings.size();
	uint32_t stringBfAddress = 8 + (numStrings * 0xC);
	std::stringstream stringBuffer;

	/* Format SDB header */
	WriteUInt32(&outFile, (useMangleBuffer) ? SDB_MANGLED : SDB_NO_MANGLING);
	WriteUInt32(&outFile, numStrings);

	/* Write each entry to filestream */
	for (auto& entry : m_strings)
	{
		std::string sdbString = entry.string;
		if (useMangleBuffer)
			mangleString(sdbString, stringBfAddress);

		WriteUInt32(&outFile, stringBfAddress);
		WriteUInt32(&outFile, sdbString.size());
		WriteUInt32(&outFile, entry.guid);

		stringBuffer.write(sdbString.c_str(), sdbString.size() + 1);
		stringBfAddress += sdbString.size() + 1;
	}

	/* Append string buffer to save file */
	auto strings = stringBuffer.str();
	outFile.write(strings.data(), strings.size());
}
