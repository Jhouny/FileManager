#include "stdafx.h"
#include "dirops.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <directory>" << std::endl;
        return 1;
    }
    std::string directory = argv[1];
    OrganizeFiles(directory);
    return 0;
}