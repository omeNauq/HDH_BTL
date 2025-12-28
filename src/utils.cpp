#include "utils.h"
#include <fstream>

bool fileExists(const std::string& path) {
    std::ifstream f(path);
    return f.good();
}
