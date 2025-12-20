#ifndef COMPILER_H
#define COMPILER_H

#include <string>

enum CompileStatus {
    COMPILE_SUCCESS,
    COMPILE_ERROR
};

struct CompileResult {
    CompileStatus status;
    std::string message;      // thông báo lỗi hoặc thông tin
};

class Compiler {
public:
    static CompileResult compile(
        const std::string& sourcePath,   // submissions/solution.cpp
        const std::string& outputPath    // bin/student_program
    );
};

#endif
