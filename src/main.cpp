#include <iostream>
#include "compiler.h"
#include "runner.h"
#include "judge.h"
#include "utils.h"

int main() {
    // 1. Compile
    CompileResult c = Compiler::compile(
        "submissions/solution.cpp",
        "bin/user_program"
    );

    if (c.status != COMPILE_SUCCESS) {
        std::cout << "Compile Error: " << c.message << "\n";
        return 0;
    }

    std::cout << "Compile OK\n";

    int testIndex = 1;
    int passed = 0;
    int total  = 0;

    while (true) {
        std::string input    = "tests/input"    + std::to_string(testIndex) + ".txt";
        std::string expected = "tests/expected" + std::to_string(testIndex) + ".txt";

        if (!fileExists(input) || !fileExists(expected)) {
            break; // hết test
        }

        total++;

        RunResult r = Runner::run(
            "bin/user_program",
            input,
            2
        );

        if (r.status != RUN_SUCCESS) {
            std::cout << "Test " << testIndex << ": "
                      << r.message << "\n";
        } else {
            JudgeResult j = Judge::judge(
                r.output,
                expected,
                testIndex
            );

            if (j.status == ACCEPTED) {
                passed++;
            }
        }

        testIndex++;
    }

    std::cout << "\nFinal Result: "
              << passed << " / " << total
              << " test cases passed\n";

    return 0;
}
