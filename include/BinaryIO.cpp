#include "BinaryIO.h"
#include <fstream>
#include <windows.h> 
#include <winsock.h>
#include <istream>
#include <vector>
#include <sstream>
using namespace std;

uint8_t 
BinaryIO::extractValue(uint32_t value, uint8_t place) {
	return (value >> (place * 8)) & 0xFF;
}
uint8_t 
BinaryIO::extractValue_64(uint64_t value, uint8_t place) {
	return (value >> (place * 8)) & 0xFF;
}

uint64_t 
BinaryIO::swapLongEndian(const uint64_t& X) {
	return _byteswap_uint64(X);
}

int8_t
BinaryIO::ReadInt8(char*& buffer) {
	int8_t value = *reinterpret_cast<const int8_t*>(buffer);
	buffer += sizeof(int8_t);
	return value;
}

uint8_t 
BinaryIO::ReadUInt8(char*& buffer) {
	uint8_t value = *reinterpret_cast<const uint8_t*>(buffer);
	buffer += sizeof(uint8_t);
	return value;
}

uint16_t
BinaryIO::ReadUInt16(char*& buffer, bool swap) {
	uint16_t value = *reinterpret_cast<const uint16_t*>(buffer);
	buffer += sizeof(uint16_t);
	return swap ? ntohs(value) : value;
}

int16_t
BinaryIO::ReadInt16(char*& buffer, bool swap) {
	int16_t value = *reinterpret_cast<const int16_t*>(buffer);
	buffer += sizeof(int16_t);
	return swap ? ntohs(value) : value;
}

uint32_t
BinaryIO::ReadUInt32(char*& buffer, bool swap) {
	uint32_t value = *reinterpret_cast<const uint32_t*>(buffer);
	buffer += sizeof(uint32_t);
	return swap ? ntohl(value) : value;
}

float
BinaryIO::ReadFloat(char*& buffer) {
	float value = *reinterpret_cast<const float*>(buffer);
	buffer += sizeof(uint32_t);
	return value;
}

uint64_t
BinaryIO::ReadUInt64(char*& buffer, bool swap) {
	uint64_t value = *reinterpret_cast<const uint64_t*>(buffer);
	buffer += sizeof(uint64_t);
	return swap ? swapLongEndian(value) : value;
}

void 
BinaryIO::WriteUInt8_CharStream(char*& buffer, const uint8_t& value) {
	*reinterpret_cast<uint8_t*>(buffer) = value;
	buffer += sizeof(uint8_t);
}

void 
BinaryIO::WriteUInt16_CharStream(char*& buffer, const uint16_t& value) {
	*reinterpret_cast<uint16_t*>(buffer) = value;
	buffer += sizeof(uint16_t);
}

void 
BinaryIO::WriteUInt32_CharStream(char*& buffer, const uint32_t& value) {
	*reinterpret_cast<uint32_t*>(buffer) = value;
	buffer += sizeof(uint32_t);
}

void 
BinaryIO::WriteUInt64_CharStream(char*& buffer, const uint64_t& value) {
	*reinterpret_cast<uint64_t*>(buffer) = value;
	buffer += sizeof(uint64_t);
}

void 
BinaryIO::WriteString_CharStream(char*& buffer, const std::string& string)
{
	int characters = string.size()+1;
	memcpy(buffer, string.c_str(), characters);
	buffer += characters;
}

void
BinaryIO::ReadData(std::istream& fileStream, size_t size, std::stringstream& stream) {
	std::vector<char> buffer;
	buffer.resize(size);
	fileStream.read(buffer.data(), size);

	stream.write(buffer.data(), size);
	return;
}

void
BinaryIO::ReadData(std::istream& fileStream, size_t size, std::vector<char>& buffer) {
	buffer.resize(size);
	fileStream.read(buffer.data(), size);
	return;
}

std::string
BinaryIO::ReadString(istream& fs, int size) {
	std::string value;
	value.resize(size);
	fs.read(&value[0], size);

	// Remove any trailing null characters
	size_t nullPos = value.find('\0');
	if (nullPos != std::string::npos)
		value.resize(nullPos);

	return value;
}

int 
BinaryIO::ReadInt(istream& fs) {

	int value = 0;
	fs.read((char*)&value, 4);

	return value;
}

unsigned int 
BinaryIO::ReadUInt(istream& in) {

	unsigned int value = 0;
	in.read((char*)&value, 4);

	return value;
}

uint32_t 
BinaryIO::ReadUInt32(istream& in) {

	uint32_t value = 0;
	in.read((char*)&value, 4);

	return value;
}

int8_t 
BinaryIO::ReadSInt8(istream& in) {

	int8_t value = 0;
	in.read((char*)&value, 1);

	return value;
}

int16_t 
BinaryIO::ReadSInt16(istream& in) {

	int16_t value = 0;
	in.read((char*)&value, 2);

	return value;
}

int32_t 
BinaryIO::ReadSInt32(istream& in) {

	int32_t value = 0;
	in.read((char*)&value, 4);

	return value;
}

uint64_t 
BinaryIO::ReadUInt64(istream& in) {
	uint64_t value = 0;
	in.read((char*)&value, sizeof(uint64_t));
	return value;
}

unsigned short 
BinaryIO::ReadUShort(istream& in) {

	unsigned short value = 0;
	in.read((char*)&value, 2);

	return value;
}

short 
BinaryIO::ReadShort(istream& in) {

	short value = 0;
	in.read((char*)&value, 2);

	return value;
}

uint8_t 
BinaryIO::ReadByte(istream& in) {

	uint8_t value = 0;
	in.read((char*)&value, 1);

	return value;
}

float 
BinaryIO::ReadFloat(istream& in) {

	float value = 0;
	in.read(reinterpret_cast<char*>(&value), sizeof(uint32_t));

	return value;
}

bool 
BinaryIO::ReadBool(istream& in) {
	return (ReadByte(in) != 0);
}

void 
BinaryIO::WriteUInt64(ofstream* fs, uint64_t value) {
	fs->write(reinterpret_cast<char*>(&value), sizeof(uint64_t));
}
void 
BinaryIO::WriteUInt32(ofstream* fs, uint32_t value) {
	fs->write(reinterpret_cast<char*>(&value), sizeof(uint32_t));
}
void
BinaryIO::WriteUInt16(ofstream* fs, uint16_t value) {
	fs->write(reinterpret_cast<char*>(&value), sizeof(uint16_t));
}
void
BinaryIO::WriteByte(ofstream* fs, uint8_t value) {
	fs->write(reinterpret_cast<char*>(&value), sizeof(uint8_t));
}
void
BinaryIO::WriteBool(ofstream* fs, bool flag) {
	fs->write(reinterpret_cast<char*>(&flag), sizeof(bool));
}
void 
BinaryIO::WriteInt32(ofstream* fs, int32_t value) {
	fs->write(reinterpret_cast<char*>(&value), sizeof(int32_t));
}
void
BinaryIO::WriteFloat(ofstream* fs, float value) {
	fs->write(reinterpret_cast<char*>(&value), sizeof(float));
}
void
BinaryIO::WriteString(ofstream* fs, std::string string) {
	fs->write(string.c_str(), string.size() + 1);
}
void 
BinaryIO::WriteChars(ofstream* fs, std::string value) {
	WriteUInt32(fs, value.size() + 1);
	fs->write(value.c_str(), value.size() + 1);
}
void 
BinaryIO::WriteSignature(ofstream* fs, std::string value) {
	uint32_t* streamHeader = reinterpret_cast<uint32_t*>(&value);
	*streamHeader = ntohl(*streamHeader);
	WriteUInt32(fs, *streamHeader);
}

void 
BinaryIO::WriteUInt64(std::stringstream& ss, uint64_t value, bool swap) {
	if (swap)
		value = swapLongEndian(value);
	ss.write(reinterpret_cast<const char*>(&value), sizeof(uint64_t));
}
void 
BinaryIO::WriteUInt32(std::stringstream& ss, uint32_t value, bool swap) {
	if (swap)
		value = ntohl(value);
	ss.write(reinterpret_cast<const char*>(&value), sizeof(uint32_t));
}
void 
BinaryIO::WriteUInt16(std::stringstream& ss, uint16_t value) {
	ss.write(reinterpret_cast<const char*>(&value), sizeof(uint16_t));
}
void 
BinaryIO::WriteByte(std::stringstream& ss, uint8_t value) {
	ss.write(reinterpret_cast<const char*>(&value), sizeof(uint8_t));
}
void 
BinaryIO::WriteBool(std::stringstream& ss, bool flag) {
	ss.write(reinterpret_cast<const char*>(&flag), sizeof(bool));
}
void 
BinaryIO::WriteInt32(std::stringstream& ss, int32_t value) {
	ss.write(reinterpret_cast<const char*>(&value), sizeof(int32_t));
}
void 
BinaryIO::WriteFloat(std::stringstream& ss, float value) {
	ss.write(reinterpret_cast<const char*>(&value), sizeof(float));
}

void 
BinaryIO::WriteString(std::stringstream& ss, const std::string& str) {
	WriteChars(ss, str);
}
void 
BinaryIO::WriteChars(std::stringstream& ss, const std::string& value) {
	WriteUInt32(ss, value.size() + 1);
	ss.write(value.c_str(), value.size() + 1);
}
void 
BinaryIO::WriteSignature(std::stringstream& ss, const std::string& value) {
	uint32_t streamHeader = *reinterpret_cast<const uint32_t*>(value.c_str());
	streamHeader = ntohl(streamHeader);
	WriteUInt32(ss, streamHeader);
}


