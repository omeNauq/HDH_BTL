#ifndef JUDGE_H
#define JUDGE_H

#include <string>

enum JudgeStatus {
    ACCEPTED,
    WRONG_ANSWER
};

struct JudgeResult {
    JudgeStatus status;
    std::string message;
};

class Judge {
public:
    static JudgeResult judge(
        const std::string& outputFile,
        const std::string& expectedFile
    );
};

#endif
