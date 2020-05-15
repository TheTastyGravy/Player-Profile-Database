#include "FileHandler.h"


FileHandler::FileHandler(std::string path)
{
	// Open the file in read mode first, in case it doesnt exist, as
	// opening a file in write will prevent a file from being created
	std::ofstream file;
	file.open(path, std::ios::binary | std::ios::app);
	file.close();

	//if file does not exist, add some data to it. must be out of order so it can be sorted


	this->path = path;
}

FileHandler::~FileHandler()
{
}



void FileHandler::loadData(Profile* profiles)
{
	// Open the file in read mode
	std::ifstream file;
	file.open(path, std::ios::binary);


	// Loop dependant on the file, not i
	for (int i = 0; !file.eof() && file.peek() != EOF; i++)
	{
		Profile record;

		file.read((char*)&record, sizeof(Profile));

		// Add the profile to the array
		profiles[i] = record;
	}

	// Return to the start of the file
	file.close();
}

bool FileHandler::updateRecord(Profile* record, Profile* newRecord)
{
	std::fstream file;
	file.open(path, std::ios::in | std::ios::out | std::ios::binary);

	// Hold the current record
	Profile temp;

	// While not fail OR eof
	while (!(file.fail() || file.eof())) 
	{
		// Read each record
		file.read((char*)&temp, sizeof(Profile));

		// Check if the names match
		if (strcmp(temp.name, record->name) == 0) 
		{
			// Get the record's position
			file.seekp(file.tellg() - (std::ios::streampos)sizeof(Profile));
			// Replace the record
			file.write((char*)newRecord, sizeof(Profile));

			file.close();
			// Record exists; return true
			return true;
		}
	}


	file.close();
	// Record does not exist; return false
	return false;
}

void FileHandler::newRecord(Profile* record)
{
	// Open the file in writing mode
	std::ofstream file;
	file.open(path, std::ios::binary | std::ios::app);
	
	// Write the record into the file
	file.write((char*)record, sizeof(Profile));

	file.close();
}