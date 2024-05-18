cmake_minimum_required(VERSION 3.28)
project(LexicalAnalyzer C)

set(CMAKE_C_STANDARD 11)

add_executable(LexicalAnalyzer main.c
        fsmbyLine.c
        fsmbyLine.h)
