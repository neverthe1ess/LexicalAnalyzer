/* 작성자 : 컴퓨터공학과 3학년 김태희(20201101), 조희원(20201086)
 * 작성일자 : 2024/05/26
 * 코드에 대한 설명: 이 코드는 메인 함수에서 입력값을 받아 의미가 있는 단위인 토큰 단위를 쪼개는 기능을 수행함.
 * */
#define _CRT_SECURE_NO_WARNINGS
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tokenizer.h"

/* 선택적 동적 메모리 반환을 위한 변수임. comment 토큰은 동적 할당 후 main으로 토큰을 반환하는데
 * 다른 토큰들과 구분되지 않아 정적 할당된 일반 토큰들을 free() 할 수 있는 문제를 막기 위함임.  */
bool isMallocVar = false;

static char *nextCheckToken = NULL;  // static global 변수로 함수가 다시 호출되어도 호출될때 초기화 되지 않음.

char *generalTokenizer(char *line) {
    static bool existSemiColons = false; // 10;과 같이 붙어 있는 세미콜론 제거를 위한 변수, 토큰 검사시 True 전환
    static bool existEqualSign = false; // =10과 같이 붙어 있는 구분자 분리를 위한 변수, 토큰 검사시 True 전환

    char *startOfToken;
    char *startOfCommentToken;

    // 세미콜론을 발견 뒤 다음 토큰 반환에서 세미콜론 반환
    if (existSemiColons) {
        existSemiColons = false;
        return ";"; // 세미콜론 토큰 분리 후 다시 False
    }

    // 새로운 입력값 진입
    if (line != NULL) {
        nextCheckToken = line;
    }

    // 문장의 끝, 더 이상 반환할 토큰이 없음.
    if (nextCheckToken == NULL || *nextCheckToken == '\0') {
        return NULL;
    }

    startOfToken = nextCheckToken;

    // 구분자나 주석기호, 따옴표, 널이 될 때까지, 즉 토큰 끝까지 이동
    while (*nextCheckToken != ' ' && *nextCheckToken != ';' && *nextCheckToken != '\n' && *nextCheckToken != '\0') {
            // 주석 기호 탐지 시
            if(*nextCheckToken == '/' && *(nextCheckToken + 1) == '*'){
                startOfCommentToken = nextCheckToken;
                nextCheckToken += 2; // 주석의 시작을 넘기기
                isMallocVar = true;
                return commentReader(startOfCommentToken);
            } else if (*nextCheckToken == '"'){
                nextCheckToken++;
                stringReader();
            } else {
                nextCheckToken++;
            }
    }
    // 널 포인터 삽입 및 중복된 구분자 처리
    if (*nextCheckToken == ' ') {
        *nextCheckToken = '\0';
        nextCheckToken++;
        while (*nextCheckToken == ' ') {
            nextCheckToken++;
        }
    } else if (*nextCheckToken == ';') {
        *nextCheckToken = '\0';
        nextCheckToken++;
        while (*nextCheckToken == ';') {
            nextCheckToken++;
        }
        existSemiColons = true; // 10; 토큰에서 세미콜론 검출시 True로 전환 후, 다음 토큰 분리 때 세미콜론 반환
    } else if(*nextCheckToken == '\n'){
        *nextCheckToken = '\0';
        nextCheckToken++;
        while (*nextCheckToken == '\n') {
            nextCheckToken++;
        }
    } else if(*nextCheckToken == '='){
        *nextCheckToken = '\0';
        nextCheckToken++;
        existEqualSign = true; // =10 검출시 True로 전환 후, 다음 토큰 분리 때 이퀄 사인 반환
    } else if (*nextCheckToken == '\0') {
        //입력의 끝 도달 NULL을 반환함. 즉, 더 이상 Tokenization를 수행하지 않음.
        nextCheckToken = NULL;
    }
    return startOfToken;
}

// 주석 처리 함수
char *commentReader(char *startOfToken){
    char *commentToken = malloc(MAX_LENGTH);
    char *commentStart = startOfToken;

    while (*nextCheckToken != '*' && *(nextCheckToken + 1) != '/') {
            nextCheckToken++;
            if(*nextCheckToken == '\0'){ // 주석이 닫히지 않았을 때
                printf("주석이 닫히지 않았습니다!\n");
                free(commentToken);
                isMallocVar = false;
                return "COMMENTS ERROR";
            }

            if(*nextCheckToken == '\n'){
                *nextCheckToken = ' ';
            }
    }
    if(*nextCheckToken == '*' && *(nextCheckToken + 1) == '/'){
        nextCheckToken += 2;
        strncpy(commentToken, commentStart, nextCheckToken - commentStart);
        commentToken[nextCheckToken - commentStart] = '\0';  // strncpy 함수는 not guarantee to NUL terminate임. 명시적인 널 삽입 필요함.
    }
    return commentToken;
}


// 문자열 처리 함수
void *stringReader(){
    while(*nextCheckToken != '"' && *nextCheckToken != '\0' && *nextCheckToken != '\n'){
        nextCheckToken++;
    }

    if(*nextCheckToken == '"'){
        nextCheckToken++;
    }
    return NULL;
}

