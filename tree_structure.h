#include "stdafx.h"
#include <regex>

// Defines the month and year structure
// of the tree
struct TreeStructure {
    std::string month;
    std::string year;
};

// Extracts the appropriate tree structure 
// from the input file: month and year
TreeStructure GetTreeStructure(const std::string& input_file);