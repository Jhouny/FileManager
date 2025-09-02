#pragma once

#include "stdafx.h"

// This function will return the size of the file in bytes
size_t GetFileSize(const std::string& filename);

// This function will retrieve the name of the file 
// (no extensions and no path)
std::string GetFileName(const std::string& filename);