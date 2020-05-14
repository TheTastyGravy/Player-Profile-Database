#include "FileHandler.h"


FileHandler::FileHandler(std::string path)
{
	// Open the file in read mode first, in case it doesnt exist, as
	// opening a file in write will prevent a file from being created
	std::ofstream file;
	file.open(path, std::ios::binary | std::ios::app);
	file.close();

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
	// ios::app is used to prevent errasing data
	std::fstream file;
	file.open(path, std::ios::binary | std::ios::app);
	// Reset put pos; ios::app sets it to the end
	file.seekp(std::ios::beg);

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