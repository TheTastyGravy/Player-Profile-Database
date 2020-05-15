#include <iostream>
#include "GameDefines.h"
#include "FileHandler.h"
#include "Profile.h"




const int DATABASE_SIZE = 100;


// Sorts 'database' in alphabetical order
void sortDatabase(Profile* database);
// Find the larges used index in 'database'
int getDatabaseSize(Profile* database);


// Get inputcommand from user and return a command code
int getInput();
// Performs a binary search for a record of 'name' in 'database', and sets 'ptrRef' to it
// Returns false if the record does not exist
bool searchRecords(Profile* database, std::string name, Profile*& ptrRef);
// Return a profile with user entered values
Profile getUserProfile();
// Check if the user wants to exit the program
bool isClosing();




int main()
{
    // Setup terminal to use escape sequences
    if (!enableVirtualTerminal())
    {
        print("The virtural terminal processing mode could not be activated.");
        print("Press 'Enter' to exit");
        std::cin.get();
        return 1;
    }


    // Used to access data file
    FileHandler file("data.bin");

    // Dynamicaly allocate array
    Profile* database = new Profile[DATABASE_SIZE];
    // Load data into array, then sort it
    file.loadData(database);
    sortDatabase(database);


    // Set to true when the player wants to close
    bool exit = false;
    // Holds the record from the database after searching
    Profile* selectedRecord = nullptr;


    // Game loop
    while (!exit)
    {
        // Set cursor position to the top and clear screen
        std::cout << CSI << "1;0H";
        clearLines(10);


        // Get input, then execute it using the command code
        int command = getInput();

        if (command == 0)
        {
            print("Invalid command");
        }
        else if (command == SEARCH)
        {
            // Get profile name from user
            std::cout << "Enter name to search for:" << INDENT;
            std::string name;
            std::cin >> name;

            // Search the database for the user's name
            if (searchRecords(database, name, selectedRecord))
            {
                print("Record found");

                // Display the record
                print(INDENT << "Name: " << (*selectedRecord).name);
                print(INDENT << "Score: " << (*selectedRecord).score);
            }
            else
                print("Record does not exist");
        }
        else if (command == EDIT)
        {
            // There must be a selected record to edit
            if (selectedRecord != nullptr)
            {
                Profile newRecord = getUserProfile();

                // Update the record in the file and database, then re-sort
                file.updateRecord(selectedRecord, &newRecord);
                *selectedRecord = newRecord;
                sortDatabase(database);

                print("Edit successful");
            }
            else
                print("No record selected; select a record first");
        }
        else if (command == CREATE)
        {
            Profile newRecord = getUserProfile();

            // Add record to file
            file.newRecord(&newRecord);

            // Put the record in an empty slot, then sort the database
            int index = getDatabaseSize(database) + 1;
            database[index] = newRecord;
            sortDatabase(database);
        }
        

        // Exit if the user wants to
        exit = isClosing();
    }
    

    delete[] database;
    //delete selectedRecord;
    return 0;
}



void sortDatabase(Profile* database)
{

}

int getDatabaseSize(Profile* database)
{
    // Iterate through the array until an empty element is found
    for (int i = 0; i < DATABASE_SIZE; i++)
    {
        // The default value for score, therefore it is empty
        if (database[i].score == -842150451)
            return i;
    }

    // If it doesnt return, the array is full, so return max index
    return DATABASE_SIZE - 1;
}


int getInput()
{
    // Clear input buffer to avoid false input
    clearBuffer();

    // Prompt user, move cursor, and get input
    std::cout << "Enter command:" << INDENT;
    std::string command;
    std::cin >> command;

    // Return correct command code
    if (command == "search")
        return SEARCH;
    else if (command == "edit")
        return EDIT;
    else if (command == "create")
        return CREATE;
    else   // Unrecognised command
        return 0;
}

bool searchRecords(Profile* database, std::string name, Profile*& ptrRef)
{
    // The databases limits
    int lower = 0;
    int upper = getDatabaseSize(database);

    // strcmp only accepts char arrays
    char charName[20];
    strcpy_s(charName, name.c_str());

    // Binary search
    while (lower <= upper)
    {
        // Set to the center of the range
        int mid = lower + (upper - lower) / 2;

        // The names match
        if (std::strcmp(database[mid].name, charName) == 0)
        {
            // Set ref to the correct record
            ptrRef = &database[mid];
            return true;
        }
        // To the right
        else if (std::strcmp(database[mid].name, charName) < 0)
            lower = mid + 1;
        // To the left
        else
            upper = mid - 1;
    }
    
    // The record doesnt exist
    return false;
}

Profile getUserProfile()
{
    // Get values
    std::string name;
    int score;
    std::cout << "Enter name:" << INDENT;
    std::cin >> name;
    std::cout << "Enter score:" << INDENT;
    std::cin >> score;

    // Invalid int; get new score
    while (std::cin.fail())
    {
        clearBuffer();
        std::cout << "Score must be an integer; try again:" << INDENT;
        std::cin >> score;
    }


    // Set the record's values
    Profile newRecord;
    strcpy_s(newRecord.name, name.c_str());
    newRecord.score = score;

    return newRecord;
}

bool isClosing()
{
    // Prompt user, move cursor, and get input
    std::cout << "Do you want to exit? y / n" << INDENT;
    char ans;
    std::cin >> ans;

    // If the input failed or was wrong, get new input
    while (std::cin.fail() || (ans != 'y' && ans != 'n'))
    {
        // Clear buffer to remov the last input, and try again
        clearBuffer();
        // Move up 2 lines and ask again
        print("Invalid responce; try again");
        std::cin >> ans;
    }

    // Return true if the wants to exit
    return (ans == 'y');
}