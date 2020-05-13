#include "FileHandler.h"


FileHandler::FileHandler(std::string path)
{
	// Open the file in read mode first, in case it doesnt exist, as
	// opening a file in write will prevent a file from being created
	file.open(path, std::ios::out | std::ios::binary);
	file.close();
	// Open the file as binary in read/write mode
	file.open(path, std::ios::in | std::ios::out | std::ios::binary);
}

FileHandler::~FileHandler()
{
	// Close the file when the object is deleted
	file.close();
}



void FileHandler::LoadData(Profile* profiles)
{
	// Move to the end of the file and get the position for the size
	file.seekg(std::ios::end);
	unsigned int fileSize = file.tellg();

	// The file only consists of records, so read the whole thing
	file.read((char*)profiles, fileSize);
}

bool FileHandler::UpdateRecord(Profile* record, Profile* newRecord)
{
	// Hold the current record
	Profile temp;

	// While not eof OR fail
	while (!(file.fail() || file.eof())) 
	{
		// Read each record
		file.read((char*)&temp, sizeof(Profile));

		// Check name
		if (temp.name == record->name) 
		{
			// Get the record's position
			file.seekp(file.tellg() - (std::ios::streampos)sizeof(Profile));
			// Replace the record
			file.write((char*)newRecord, sizeof(Profile));

			// Record exists; return true
			return true;
		}
	}

	// Record does not exist; return false
	return false;
}

void FileHandler::NewRecord(Profile* record)
{
	// Write to the end of the file
	file.seekp(std::ios::end);

	// Write the record into the file
	file.write((char*)record, sizeof(Profile));
}