#include "runner.h"
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <cstring>
#include <ctime>

RunResult Runner::run(
    const std::string& programPath,
    const std::string& inputFile,
    int timeLimitSec
) {
    int pipefd[2];
    pipe(pipefd);

    pid_t pid = fork();

    if (pid == 0) {
        // CHILD
        int inFd = open(inputFile.c_str(), O_RDONLY);
        dup2(inFd, STDIN_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);

        close(pipefd[0]);
        close(pipefd[1]);

        execl(programPath.c_str(), programPath.c_str(), NULL);
        _exit(1);
    }

    // PARENT
    close(pipefd[1]);

    std::string output;
    char buffer[1024];
    int status;
    time_t start = time(nullptr);

    while (true) {
        if (waitpid(pid, &status, WNOHANG) > 0) break;

        if (time(nullptr) - start > timeLimitSec) {
            kill(pid, SIGKILL);
            return { TIME_LIMIT_EXCEEDED, "", "Time Limit Exceeded" };
        }

        usleep(1000);
    }

    ssize_t n;
    while ((n = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
        output.append(buffer, n);
    }

    close(pipefd[0]);

    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        return { RUN_SUCCESS, output, "OK" };
    }

    return { RUNTIME_ERROR, output, "Runtime Error" };
}
