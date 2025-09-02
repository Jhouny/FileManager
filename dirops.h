#pragma once

#include "stdafx.h"
#include <vector>
#include "tree_structure.h"
#include "fileops.h"

// Retrieves all the files in a directory 
// and it's subdirectories
std::vector<std::string> GetFilesInDirectory(const std::string& directory);

// Moves a file from one directory to another
bool MoveFile(const std::string& source, const std::string& destination);

// Organizes all files in a directory by year and month
void OrganizeFiles(const std::string& directory);

// Moves all files to the parent directory
void MoveFilesToParent(const std::string& directory);

// Copy files from one directory to another and organize them
void CopyAndOrganize(const std::string& source, const std::string& destination);