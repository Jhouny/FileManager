#include "fileops.h"

// Returns the size of the file in bytes
size_t GetFileSize(const std::string& filename) {
    fs::path p(filename);
    return fs::file_size(p);
}

// Retrieves the name of the file 
// (no extensions and no path)
std::string GetFileName(const std::string& filename) {
    return fs::path(filename).stem().string();
}