// StringDB_Cryptor.cpp : This file contains the 'main' function. Program execution begins and ends there. //
#include "stringdatabase.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) 
{
	// Check if at least one command-line argument is provided
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <SDB_FILE_PATH>\n" << std::endl;
		return 1; }

	// Extract the file path from the CLI arguments
	std::string filePath = argv[1];

	/* Load the database into a CSDB object */
	bool swapMangleMode;
	CStringDatabase example(filePath.c_str());
	example.load();

	/* Save into an unmangled/mangled database */
	swapMangleMode = !example.isMangled();
	example.save(swapMangleMode);

	/* 'press enter to exit' prompt */
	printf("Saved file is encrypted: %s\n", (swapMangleMode) ? "true" : "false");
	system("pause");
}

