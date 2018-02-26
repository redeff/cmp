#!/bin/bash

problem=books

g++ -std=c++11 -Wconversion -Wshadow -Wall -Wextra -O2 -pg grader.cpp main.cpp -o prog
