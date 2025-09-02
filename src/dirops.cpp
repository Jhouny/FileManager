#include "dirops.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>

// This function will retrieve all the files in a directory and it's subdirectories
std::vector<std::string> GetFilesInDirectory(const std::string& directory) {
    std::vector<std::string> files;
    try {
        for (const auto& entry : fs::recursive_directory_iterator(directory)) {
            try {
                if (entry.is_regular_file()) {
                    files.push_back(entry.path().string());
                }
            } catch (const fs::filesystem_error& e) {
                LogMessage("Error accessing file: " + entry.path().string() + " - " + std::string(e.what()));
                continue; // Skip this file and continue with others
            }
        }
    } catch (const fs::filesystem_error& e) {
        LogMessage("Error accessing directory: " + directory + " - " + std::string(e.what()));
    }
    return files;
}

// Utility function to log messages to a file
void LogMessage(const std::string& message) {
    std::ofstream logFile("operation_log.txt", std::ios::app);
    if (logFile.is_open()) {
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        logFile << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S") << " - " << message << std::endl;
    }
}

// Moves a file from one directory to another
bool MoveFile(const std::string& source, const std::string& destination) {
    try {
        fs::path destPath(destination);
        if (fs::exists(destPath)) {
            std::string newFileName = destPath.stem().string() + "_copy" + destPath.extension().string();
            std::string srcDir = fs::path(source).parent_path().string();
            return MoveFile(source, srcDir + "/" + newFileName);
        }
        fs::rename(source, destPath);
        LogMessage("Moved file: " + source + " to " + destPath.string());
        return true;
    } catch (const fs::filesystem_error& e) {
        LogMessage("Error moving file: " + source + " - " + std::string(e.what()));
        return false;
    }
}

// Organizes all files in a directory by year and month
void OrganizeFiles(const std::string& directory, bool dryRun) {
    for (const auto& file : GetFilesInDirectory(directory)) {
        // Extracts the year and month to put the file in the appropriate directory
        TreeStructure tree_structure = GetTreeStructure(file);
        if (tree_structure.month == "Invalid file name" || tree_structure.year == "Invalid file name") {
            LogMessage("Skipped invalid file: " + file);
            continue;
        }
        std::string dst = directory + "/" + tree_structure.year + "/" + tree_structure.month;
        if (!fs::is_directory(fs::path(dst))) {
            if (!dryRun) {
                try {
                    fs::create_directories(dst);
                } catch (const fs::filesystem_error& e) {
                    LogMessage("Error creating directory: " + dst + " - " + std::string(e.what()));
                }
            }
            
            LogMessage("Created directory: " + dst);
        }
        if (!dryRun)
            MoveFile(file, dst + "/" + fs::path(file).filename().string());
        else
            LogMessage("Dry-run: Would move file: " + file + " to " + dst);
    }
}

// Moves all files to the parent directory
void MoveFilesToParent(const std::string& directory, bool dryRun) {
    for (const auto& file : GetFilesInDirectory(directory)) {
        std::string dest = directory + "/" + fs::path(file).filename().string();
        if (!dryRun)
            MoveFile(file, dest);
        else
            LogMessage("Dry-run: Would move file: " + file + " to " + dest);
    }
}

// Copy files from one directory to another and organize them
void CopyAndOrganize(const std::string& source, const std::string& destination) {
    
}