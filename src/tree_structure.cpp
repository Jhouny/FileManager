#include "tree_structure.h"
#include "fileops.h"

// Extracts the appropriate tree structure 
// from the input file: month and year
TreeStructure GetTreeStructure(const std::string& input_file) {
    std::string month;
    std::string year;
    std::smatch match;
    fs::file_time_type f_last_write = fs::last_write_time(fs::path(input_file));
    std::string filename = GetFileName(input_file);
    if (!std::regex_search(filename, match, std::regex("[21]\\d{3}([-_])?[01]\\d([-_])?[0-3]\\d"))) {
        auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(f_last_write - fs::file_time_type::clock::now() + std::chrono::system_clock::now());
        std::time_t cftime = std::chrono::system_clock::to_time_t(sctp);
        std::tm* tm = std::localtime(&cftime);
        year = std::to_string(1900 + tm->tm_year);
        month = (tm->tm_mon + 1 < 10 ? "0" : "") + std::to_string(tm->tm_mon + 1);
        
        auto now = std::chrono::system_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::months>(now - sctp).count();
        if (diff < 3)
            return {"Invalid file name and file is too recent", "Invalid file name and file is too recent"};
        return { month, year };
    }
    year = match.str().substr(0, 4);
    // If it matches the format YYYY-MM-DD or YYYY_MM_DD
    if (std::regex_match(match.str(), std::regex("[21]\\d{3}([-_])[01]\\d([-_])[0-3]\\d")))
        month = match.str().substr(5, 2);
    else
        month = match.str().substr(4, 2);
    return { month, year };
}