#include "compiler.h"
#include <cstdlib>      // system()
#include <fstream>      // ifstream
#include <sstream>

static bool fileExists(const std::string& path) {
    std::ifstream f(path);
    return f.good();
}

CompileResult Compiler::compile(
    const std::string& sourcePath,
    const std::string& outputPath
) {
    CompileResult result;

    // 1. Kiểm tra file source có tồn tại không
    if (!fileExists(sourcePath)) {
        result.status = COMPILE_ERROR;
        result.message = "Source file not found: " + sourcePath;
        return result;
    }

    // 2. Xác định compiler dựa trên phần mở rộng
    std::string command;
    if (sourcePath.size() >= 2 &&
        sourcePath.substr(sourcePath.size() - 2) == ".c") {

        command = "gcc " + sourcePath + " -o " + outputPath;

    } else if (sourcePath.size() >= 4 &&
               sourcePath.substr(sourcePath.size() - 4) == ".cpp") {

        command = "g++ " + sourcePath + " -o " + outputPath;

    } else {
        result.status = COMPILE_ERROR;
        result.message = "Unsupported file type";
        return result;
    }

    // 3. Thực thi lệnh biên dịch
    int ret = system(command.c_str());

    // 4. Kiểm tra kết quả
    if (ret != 0 || !fileExists(outputPath)) {
        result.status = COMPILE_ERROR;
        result.message = "Compilation failed";
        return result;
    }

    // 5. Thành công
    result.status = COMPILE_SUCCESS;
    result.message = "Compilation successful";
    return result;
}
