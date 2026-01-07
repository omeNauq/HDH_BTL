#ifndef RUNNER_H
#define RUNNER_H

#include <string>

enum RunStatus {
    RUN_SUCCESS,
    RUNTIME_ERROR,
    TIME_LIMIT_EXCEEDED
};

struct RunResult {
    RunStatus status;
    std::string output;   // stdout lấy từ pipe
    std::string message;
};

class Runner {
public:
    static RunResult run(
        const std::string& programPath,
        const std::string& inputFile,
        int timeLimitSec
    );
};

#endif
