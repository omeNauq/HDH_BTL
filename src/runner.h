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
    int exitCode;
    std::string message;
};

class Runner {
public:
    static RunResult run(
        const std::string& programPath,
        const std::string& inputFile,
        const std::string& outputFile,
        int timeLimitSec
    );
};

#endif
