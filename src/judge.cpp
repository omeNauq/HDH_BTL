#include "judge.h"
#include <fstream>
#include <string>

static std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");

    if (start == std::string::npos) return "";
    return s.substr(start, end - start + 1);
}

JudgeResult Judge::judge(
    const std::string& outputFile,
    const std::string& expectedFile
) {
    std::ifstream out(outputFile);
    std::ifstream exp(expectedFile);

    if (!out.is_open() || !exp.is_open()) {
        return {
            WRONG_ANSWER,
            "Cannot open output or expected file"
        };
    }

    std::string outLine, expLine;
    int line = 1;

    while (true) {
        bool outOk = static_cast<bool>(std::getline(out, outLine));
        bool expOk = static_cast<bool>(std::getline(exp, expLine));

        if (!outOk && !expOk) {
            return {
                ACCEPTED,
                "Accepted"
            };
        }

        if (outOk != expOk ||
            trim(outLine) != trim(expLine)) {
            return {
                WRONG_ANSWER,
                "Wrong Answer at line " + std::to_string(line)
            };
        }

        line++;
    }
}
