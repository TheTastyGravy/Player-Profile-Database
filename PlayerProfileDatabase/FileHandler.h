#pragma once
#include <fstream>
#include "Profile.h"


// Used to load and save data to a binary file
class FileHandler
{
public:
	// Open the file at 'path'. If one does not exist, create one
	FileHandler(std::string path);
	// Close the file
	~FileHandler();


	// Load the file's data into 'profiles' array
	void LoadData(Profile* profiles);
	// Replace 'record's data on file with 'newRecord'
	bool UpdateRecord(Profile* record, Profile* newRecord);
	// Add 'record' to the end of the file
	void NewRecord(Profile* record);

private:
	std::fstream file;
};