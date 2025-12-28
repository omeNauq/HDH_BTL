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

    // 2. Run tests (AUTO SCAN)
    int i = 1;
    int passed = 0;
    int total  = 0;

    while (true) {
        std::string input    = "tests/input"    + std::to_string(i) + ".txt";
        std::string expected = "tests/expected" + std::to_string(i) + ".txt";
        std::string output   = "outputs/output" + std::to_string(i) + ".txt";

        if (!fileExists(input) || !fileExists(expected)) {
            break; // hết test
        }

        total++;

        RunResult r = Runner::run(
            "bin/user_program",
            input,
            output,
            2
        );

        if (r.status != RUN_SUCCESS) {
            std::cout << "Test " << i << ": " << r.message << "\n";
            i++;
            continue;
        }

        JudgeResult j = Judge::judge(output, expected, i);

        if(j.status == ACCEPTED) {
            passed++;
        }

        i++;
    }

    // 3. Final result
    std::cout << "\nFinal Result: "
              << passed << " / " << total
              << " test cases passed\n";

    return 0;
}
