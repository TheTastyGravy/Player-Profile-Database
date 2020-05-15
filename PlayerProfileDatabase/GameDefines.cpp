#include "GameDefines.h"


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

void clearBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
}

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