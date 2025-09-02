#include "dirops.h"

// This function will retrieve all the files in a directory 
// and it's subdirectories
std::vector<std::string> GetFilesInDirectory(const std::string& directory) {
    std::vector<std::string> files;
    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().string());
        }
    }
    return files;
}

// Moves a file from one directory to another
bool MoveFile(const std::string& source, const std::string& destination) {
    try {
        fs::rename(source, destination);
        return true;
    } catch (const fs::filesystem_error& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
}

// Organizes all files in a directory by year and month
void OrganizeFiles(const std::string& directory) {
    for (const auto& file : GetFilesInDirectory(directory)) {
        // Extracts the year and month to put the file in the appropriate directory
        TreeStructure tree_structure = GetTreeStructure(file);
        if (tree_structure.month == "Invalid file name" || tree_structure.year == "Invalid file name") {
            std::cout << "Invalid file name: " << file << std::endl;
            continue;
        }
        std::string dst = directory + "/" + tree_structure.year + "/" + tree_structure.month;
        
        if(!fs::is_directory(fs::path(dst)))
            fs::create_directories(dst);

        MoveFile(file, dst + "/" + fs::path(file).filename().string());
    }
}

// Moves all files to the parent directory
void MoveFilesToParent(const std::string& directory) {
    for (const auto& file : GetFilesInDirectory(directory))
        MoveFile(file, directory + "/" + fs::path(file).filename().string());
}

// Copy files from one directory to another and organize them
void CopyAndOrganize(const std::string& source, const std::string& destination) {
    
}