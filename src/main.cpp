#include <iostream>
#include "compiler.h"
#include "runner.h"
#include <fstream>
#include "judge.h"

int main() {
    // Compile
    CompileResult result = Compiler::compile(
        "submissions/solution.cpp",
        "bin/student_program"
    );

    if (result.status == COMPILE_SUCCESS) {
        std::cout << "Compile OK\n";
    } else {
        std::cout << "Compile ERROR: " << result.message << "\n";
        return 0;
    }

    // Runner
    RunResult r = Runner::run(
    "bin/student_program",
    "tests/input1.txt",
    "outputs/output1.txt",
    2   // 2 seconds
    );

    if (r.status == RUN_SUCCESS) {
        std::cout << "Run OK\n";
        // ĐỌC OUTPUT 
        std::ifstream fin("outputs/output1.txt");
        if (fin.is_open()) {
            std::string line;
            while (std::getline(fin, line)) {
                std::cout << line << "\n";
            }
            fin.close();
        } else {
            std::cout << "Cannot open output file\n";
        }

    } else {
        std::cout << r.message << "\n";
    }

    // Judge
    JudgeResult j = Judge::judge(
    "outputs/output1.txt",
    "tests/expected1.txt"
    );

    if (j.status == ACCEPTED) {
        std::cout << "Accepted\n";
    } else {
        std::cout << j.message << "\n";
    }

    return 0;
}
