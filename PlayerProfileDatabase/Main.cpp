#include <iostream>
#include "GameDefines.h"
#include "FileHandler.h"
#include "Profile.h"



// Sorts 'database' in alphabetical order
void sortDatabase(Profile* database);


// Get inputcommand from user and return a command code
int getInput();
// Performs a binary search for a record of 'name' in 'database', and sets 'ptrRef' to it
// Returns false if the record does not exist
bool searchRecords(Profile* database, std::string name, Profile*& ptrRef);

// Check if the user wants to exit the program
bool isClosing();




// Use this to change a profile's name
//strcpy_s(thing.name, "hdg");

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

    // Dynamicaly allocate array. 100 should be large enough; change if nessesary
    Profile* database = new Profile[100];
    // Load data into array, then sort it
    file.loadData(database);
    sortDatabase(database);


    // Set to true when the player wants to close
    bool exit = false;
    // Holds the record in the array after searching
    Profile* selectedRecord = nullptr;


    // Game loop
    while (!exit)
    {
        // Set cursor position to the top and clear screen
        std::cout << CSI << "1;0H";
        clearLines(10);

        
        /*
        Profile thing { "bob", 10 };

        file.newRecord(&thing);


        thing.score = 200;

        file.newRecord(&thing);


        for (int i = 0; i < 5; i++)
        {
            std::cout << database[i].name << " " << database[i].score << std::endl;
        }
        */


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
                print("Name: " << (*selectedRecord).name);
                print("Score: " << (*selectedRecord).score);
            }
            else
                print("Record does not exist");
        }
        else if (command == EDIT)
        {
            //only if selectedRecord != null
            //get new record, then file.update()
        }
        else if (command == CREATE)
        {
            //get input, then file.newRecord()
        }
        


        // Exit if the user wants to
        exit = isClosing();
    }
    

    delete[] database;
    return 0;
}




void sortDatabase(Profile* database)
{

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
    int lower = 0;
    int upper = 100; //set to max used

    // strcmp only accepts char arrays
    const char* charName = name.c_str();

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