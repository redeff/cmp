#!/bin/bash

problem=books

g++ -std=c++11 -g -Wconversion -Wshadow -Wall -Wextra -D_GLIBCXX_DEBUG grader.cpp main.cpp -o prog
