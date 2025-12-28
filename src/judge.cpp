#include "judge.h"
#include <fstream>
#include <iostream>
#include <string>

static std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");

    if (start == std::string::npos) return "";
    return s.substr(start, end - start + 1);
}

JudgeResult Judge::judge(
    const std::string& outputFile,
    const std::string& expectedFile,
    int testIndex
) {
    std::ifstream out(outputFile);
    std::ifstream exp(expectedFile);

    if (!out.is_open() || !exp.is_open()) {
        std::cout << "Test " << testIndex << ": Wrong Answer\n";
        return { WRONG_ANSWER };
    }

    std::string outLine, expLine;

    while (true) {
        bool outOk = static_cast<bool>(std::getline(out, outLine));
        bool expOk = static_cast<bool>(std::getline(exp, expLine));

        if (!outOk && !expOk) {
            std::cout << "Test " << testIndex << ": Accepted\n";
            return { ACCEPTED };
        }

        if (outOk != expOk ||
            trim(outLine) != trim(expLine)) {
            std::cout << "Test " << testIndex << ": Wrong Answer\n";
            return { WRONG_ANSWER };
        }
    }
}
