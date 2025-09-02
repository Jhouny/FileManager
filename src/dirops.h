#pragma once

#include "stdafx.h"
#include <vector>
#include "tree_structure.h"
#include "fileops.h"

// Retrieves all the files in a directory 
// and it's subdirectories
std::vector<std::string> GetFilesInDirectory(const std::string& directory);

// Logs a message to a file
void LogMessage(const std::string& message);

// Moves a file from one directory to another
bool MoveFile(const std::string& source, const std::string& destination);

// Organizes all files in a directory by year and month with optional dry-run mode
void OrganizeFiles(const std::string& directory, bool dryRun = false);

// Moves all files to the parent directory
void MoveFilesToParent(const std::string& directory, bool dryRun = false);

// Copy files from one directory to another and organize them
void CopyAndOrganize(const std::string& source, const std::string& destination);