#pragma once
#include <fstream>
#include "Profile.h"


// Used to load and save data to a binary file
class FileHandler
{
public:
	// If the file doesnt exist, it will be created
	FileHandler(std::string path);
	~FileHandler();


	// Load the file's data into 'profiles' array
	void loadData(Profile* profiles);
	// Replace 'record's data on file with 'newRecord'
	bool updateRecord(Profile* record, Profile* newRecord);
	// Add 'record' to the end of the file
	void newRecord(Profile* record);

private:
	std::string path;
};