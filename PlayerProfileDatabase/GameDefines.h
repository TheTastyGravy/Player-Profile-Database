#pragma once
#include <iostream>
#include <Windows.h>

// Used for cleaner syntax
#define print(x) std::cout << x << std::endl



const char* const CSI = "\x1b[";
const char* const INDENT = "\x1b[5C";

// Command codes

const int SEARCH = 1;	// Search current records
const int EDIT = 2;		// Edit the currently selected record
const int CREATE = 3;	// Create new record
const int DISPLAY = 4;	// Display the database



// Set output mode to handle virtual terminal sequences
bool enableVirtualTerminal();
// Clear the input buffer after each input
void clearBuffer();
// Clear the current line, and 'n' lines below it
void clearLines(int n);