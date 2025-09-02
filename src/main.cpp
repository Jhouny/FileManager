#include "stdafx.h"
#include "dirops.h"
#include <iostream>

int main() {
    std::string directory;
    std::string dryRunInput;
    bool dryRun = false;
    int operation = 0;

    std::cout << "Enter directory path: ";
    std::getline(std::cin, directory);

    std::cout << "Dry run? (y/n): ";
    std::getline(std::cin, dryRunInput);
    dryRun = (dryRunInput == "y" || dryRunInput == "Y");

    std::cout << "Select operation:\n";
    std::cout << "1. Organize files\n";
    std::cout << "2. Move all files in sub-directories to parent directory\n"; 
    std::cout << "Enter choice (1/2): ";
    std::cin >> operation;

    switch (operation) {
        case 1:
            OrganizeFiles(directory, dryRun);
            break;
        case 2:
            MoveFilesToParent(directory, dryRun);
            break;
        default:
            std::cerr << "Invalid operation selected.\n";
            return 1;
    }
    return 0;
}