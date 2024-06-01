cmake_minimum_required(VERSION 3.28)
project(LexicalAnalyzer C)

set(CMAKE_C_STANDARD 11)

add_executable(LexicalAnalyzer main.c
        fsmbyToken.c
        fsmbyToken.h
        tokenizer.c
        tokenizer.h
        parser.c
        parser.h)
