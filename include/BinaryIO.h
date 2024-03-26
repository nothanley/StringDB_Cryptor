/* Static utility class for reading and writing stream binary */
#include <string>
#include <sstream>
#include <vector>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

#define _U64  ReadUInt64(*m_pDataStream)
#define _U32  ReadUInt32(*m_pDataStream)
#define _U16  ReadUShort(*m_pDataStream)
#define _U8  ReadByte(*m_pDataStream)
#define _S32  ReadSInt32(*m_pDataStream)
#define _BOOL ReadBool(*m_pDataStream)
#define _FLOAT ReadFloat(*m_pDataStream)
#pragma once

namespace BinaryIO {

	uint8_t extractValue(uint32_t value, uint8_t place);
	uint8_t extractValue_64(uint64_t value, uint8_t place);
	uint64_t swapLongEndian(const uint64_t& X);

	int8_t ReadInt8(char*& buffer);
	uint8_t  ReadUInt8(char*& buffer);
	uint16_t ReadUInt16(char*& buffer, bool swap = false);
	int16_t  ReadInt16(char*& buffer, bool swap = false);
	uint32_t ReadUInt32(char*& buffer, bool swap = false);
	uint64_t ReadUInt64(char*& buffer, bool swap = false);
	float ReadFloat(char*& buffer);
	void WriteUInt8_CharStream(char*& buffer, const uint8_t& value);
	void WriteUInt16_CharStream(char*& buffer, const uint16_t& value);
	void WriteUInt32_CharStream(char*& buffer, const uint32_t& value);
	void WriteUInt64_CharStream(char*& buffer, const uint64_t& value);
	void WriteString_CharStream(char*& buffer, const std::string& string);
	
    void ReadData(std::istream& fileStream, size_t size, std::stringstream& stream);
    void ReadData(istream& fileStream, size_t size, std::vector<char>& buffer);
	std::string ReadString(istream& fs, int size);

	int ReadInt(istream& fs);
	unsigned int ReadUInt(istream& in);
	uint32_t ReadUInt32(istream& in);
	int8_t ReadSInt8(istream& in);
	int16_t ReadSInt16(istream& in);
	int32_t ReadSInt32(istream& in);
	uint64_t ReadUInt64(istream& in);
	unsigned short ReadUShort(istream& in);
	short ReadShort(istream& in);
	uint8_t ReadByte(istream& in);
	float ReadFloat(istream& in);
	bool ReadBool(istream& in);

    void WriteUInt64(stringstream& ss, uint64_t value, bool swap = false);
    void WriteUInt32(std::stringstream& ss, uint32_t value, bool swap = false);
    void WriteUInt16(stringstream& ss, uint16_t value);
    void WriteByte(stringstream& ss, uint8_t value);
    void WriteBool(stringstream& ss, bool flag);
    void WriteInt32(stringstream& ss, int32_t value);
    void WriteFloat(stringstream& ss, float value);
    void WriteString(stringstream& ss, const std::string& string);
    void WriteChars(stringstream& ss, const std::string& value);
    void WriteSignature(stringstream& ss, const std::string& value);

    void WriteUInt64(ofstream* fs, uint64_t value);
    void WriteUInt32(ofstream* fs, uint32_t value);
    void WriteUInt16(ofstream* fs, uint16_t value);
    void WriteByte(ofstream* fs, uint8_t value);
    void WriteBool(ofstream* fs, bool flag);
    void WriteInt32(ofstream* fs, int32_t value);
    void WriteFloat(ofstream* fs, float value);
    void WriteString(ofstream* fs, std::string string);
    void WriteChars(ofstream* fs, std::string value);
	void WriteSignature(ofstream* fs, std::string value);

}
