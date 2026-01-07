#include "judge.h"
#include <fstream>
#include <iostream>
#include <sstream>

static std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    return s.substr(start, end - start + 1);
}

JudgeResult Judge::judge(
    const std::string& programOutput,
    const std::string& expectedFile,
    int testIndex
) {
    std::ifstream exp(expectedFile);
    if (!exp.is_open()) {
        std::cout << "Test " << testIndex << ": Wrong Answer\n";
        return { WRONG_ANSWER };
    }

    std::stringstream out(programOutput);
    std::string outLine, expLine;

    while (true) {
        bool o = static_cast<bool>(std::getline(out, outLine));
        bool e = static_cast<bool>(std::getline(exp, expLine));

        if (!o && !e) {
            std::cout << "Test " << testIndex << ": Accepted\n";
            return { ACCEPTED };
        }

        if (o != e || trim(outLine) != trim(expLine)) {
            std::cout << "Test " << testIndex << ": Wrong Answer\n";
            return { WRONG_ANSWER };
        }
    }
}
