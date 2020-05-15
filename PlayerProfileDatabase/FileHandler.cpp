#include "FileHandler.h"


FileHandler::FileHandler(std::string path)
{
	// Open the file in read mode so it doesnt create a new file
	std::ifstream ifile;
	ifile.open(path, std::ios::binary);

	// Check if the file doesnt exists
	if (!ifile.is_open())
	{
		// Create a new file using write
		std::ofstream ofile;
		ofile.open(path, std::ios::binary);

		// Fill the file with default data
		{
			Profile temp { "jack", 2450 };
			ofile.write((char*)&temp, sizeof(Profile));
		}
		{
			Profile temp { "bob", 1000 };
			ofile.write((char*)&temp, sizeof(Profile));
		}
		{
			Profile temp { "jill", 9989 };
			ofile.write((char*)&temp, sizeof(Profile));
		}
		{
			Profile temp { "amber", 4321 };
			ofile.write((char*)&temp, sizeof(Profile));
		}
		{
			Profile temp { "doug", 12345 };
			ofile.write((char*)&temp, sizeof(Profile));
		}
		



		ofile.close();
	}

	ifile.close();


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