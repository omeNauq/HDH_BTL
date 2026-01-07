# AutoJudge Mini System

A simple auto-grading system written in C++ for Operating Systems coursework.

The system automatically:

- Compiles C/C++ submissions
- Runs programs with input redirection, using redirect pipe
- Applies time limits

## Build

COMPILE:

g++ src/\*.cpp -o bin/autograder

RUN:

./bin/autograder

Notes:

bin/ and outputs/ are generated automatically at runtime and are not included in the repository.

Test cases are read from the tests/ directory.

Submission source code is located in submissions/solution.cpp.
