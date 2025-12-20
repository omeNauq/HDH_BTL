#include "runner.h"
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <cstring>

RunResult Runner::run(
    const std::string& programPath,
    const std::string& inputFile,
    const std::string& outputFile,
    int timeLimitSec
) {
    pid_t pid = fork();

    if (pid == 0) {
        // ===== CHILD PROCESS =====

        // Redirect stdin
        int inFd = open(inputFile.c_str(), O_RDONLY);
        if (inFd < 0) _exit(1);
        dup2(inFd, STDIN_FILENO);
        close(inFd);

        // Redirect stdout
        int outFd = open(outputFile.c_str(),
                         O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (outFd < 0) _exit(1);
        dup2(outFd, STDOUT_FILENO);
        close(outFd);

        // Execute student program
        execl(programPath.c_str(), programPath.c_str(), nullptr);

        // exec failed
        _exit(1);
    }

    // ===== PARENT PROCESS =====
    int status = 0;
    int elapsed = 0;

    while (true) {
        pid_t result = waitpid(pid, &status, WNOHANG);

        if (result == pid) {
            // Child finished
            if (WIFEXITED(status)) {
                return {
                    RUN_SUCCESS,
                    WEXITSTATUS(status),
                    "Run OK"
                };
            } else {
                return {
                    RUNTIME_ERROR,
                    -1,
                    "Runtime Error"
                };
            }
        }

        if (elapsed >= timeLimitSec) {
            kill(pid, SIGKILL);
            return {
                TIME_LIMIT_EXCEEDED,
                -1,
                "Time Limit Exceeded"
            };
        }

        sleep(1);
        elapsed++;
    }
}
