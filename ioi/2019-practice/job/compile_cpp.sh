#!/bin/bash

problem=job
g++ -std=c++11 -o $problem grader.cpp $problem.cpp -Wall -Wextra -Wshadow -Wconversion -g -DGLIBCXX_DEBUG
