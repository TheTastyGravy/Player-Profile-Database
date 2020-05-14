#include <iostream>
#include <limits>
#include <Windows.h>
#include "FileHandler.h"
#include "Profile.h"
// max is defined twice
#undef max

// Used for cleaner syntax
#define print(x) std::cout << x << std::endl



const char* CSI = "\x1b[";

const char* INDENT = "\x1b[5C";




// Set output mode to handle virtual terminal sequences
bool enableVirtualTerminal()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
        return false;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
        return false;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    return (SetConsoleMode(hOut, dwMode));
}
// Clear the input buffer after each input
void clearBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
// Clear the current line, and n lines below it
void clearLines(int n)
{
    // Clear the current line
    std::cout << CSI << "2K";

    // Go down clearing lines
    for (int i = 0; i < n; i++)
    {
        std::cout << CSI << "B";
        std::cout << CSI << "2K";
    }
    // Return to the starting line
    std::cout << CSI << n << "A";
}




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
    Profile* arr = new Profile[100];
    // Load data into array
    file.loadData(arr);
    //---sort---

    // Set to true when the player wants to close
    bool exit = false;


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
            std::cout << arr[i].name << " " << arr[i].score << std::endl;
        }
        */



        // Prompt user, move cursor, and get input
        std::cout << "Enter command:" << INDENT;
        std::string val;
        std::cin >> val;





        //if search, go through array with binary

        //if edit after search, get new record, then file.update()

        //if new record, get input, then file.newRecord()



        

        // Exit if the user wants to
        exit = isClosing();
    }
    

    delete[] arr;
    return 0;
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