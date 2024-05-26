/* 작성자 : 컴퓨터공학과 3학년 김태희(20201101), 조희원(20201086)
 * 작성일자 : 2024/05/26
 * 코드에 대한 설명: 이 코드는 메인 함수에서 한 줄 단위로 입력받아 의미가 있는 단위인 토큰 단위를 쪼개는 기능을 수행함.
 * */

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "tokenizer.h"

char *tokenize(char *line) {
    static char *nextCheckToken = NULL;
    bool TokenState1 = false;  // String 상태
    bool TokenState2 = false;  // 주석 상태
    bool StringStart = false;  // 첫 번째 "를 위한 변수
    // 새로운 문장 진입
    if (line != NULL) {
        nextCheckToken = line;
    }


    if(TokenState1 == false && TokenState2 == false){
        if(*nextCheckToken == '/' && *(nextCheckToken + 1) == '*'){
            TokenState2 = true;
        } else if (*nextCheckToken == '"'){
            StringStart = true;
            TokenState1 = true;
        }
    }

    if(TokenState2 == true){
        if(*nextCheckToken == '*' && *(nextCheckToken + 1) == '/'){
            TokenState2 = false;
        }
    }


    char *tmpCheckToken = nextCheckToken;
    while(*tmpCheckToken != '/' && *(tmpCheckToken + 1) != '*'){
        tmpCheckToken++;
        if(*tmpCheckToken == '/' && *(tmpCheckToken + 1) == '*'){
            TokenState2 = true;
        }
    }


    int i = 0;

    while (line[i] != '\0') {
        if (TokenState1 == false && TokenState2 == false) {
            if (line[i] == '/' && line[i + 1] == '*') { //comments
                TokenState2 = true;
                i += 2;
                continue;
            }
            if (line[i] == '"') { //string
                StringStart = true;
                TokenState1 = true;
                i++;
                continue;
            }
        }

        if (TokenState2 == true) { // 주석 기호 /* 가 이미 들어왔을 때
            if (line[i] == '*' && line[i + 1] == '/') {
                TokenState2 = false;
                i += 2;
                continue;
            }
            i++;
            continue;
        }

        if (TokenState1 == true) {
            if (line[i] == '"') {
                TokenState1 = false;
            } else if (line[i] == '\0') {
                TokenState1 = false;
            }
            i++;
            continue;
        }

        if (StringStart == true) {
            StringStart = false;
        }

        // 1-3: 일반 토큰 처리
        if (TokenState1 == false && TokenState2 == false) {
            // 토큰 분리 및 출력
            char* token = generalTokenizer(&line[i]);
            if (token != NULL) {
                printf("Token: %s\n", token);
                i += strlen(token);
            } else {
                i++;
            }
        }
    }

    // 추가 필요 부분: 주석이 종료되지 않은 경우 처리
    if (TokenState2 == true) {
        printf("Error: Comment not terminated.\n");
    }
}


char *generalTokenizer(char *line) {
    static char *nextCheckToken = NULL;  // static 변수로 함수가 다시 호출되어도 호출될때 초기화 되지 않음.
    static bool ExistSemiColons = false; // 10; 붙어 있는 세미콜론 제거를 위한 변수, 10;  토큰 검사시 True 전환
    char *startOfToken;

    // 세미콜론을 발견 뒤 다음 토큰 반환에서 세미콜론 반환
    if (ExistSemiColons) {
        ExistSemiColons = false;
        return ";"; // 세미콜론 토큰 분리 후 다시 False
    }
    // 새로운 문장 진입
    if (line != NULL) {
        nextCheckToken = line;
    }

    // 문장의 끝, 더 이상 반환할 토큰이 없음.
    if (nextCheckToken == NULL || *nextCheckToken == '\0') {
        return NULL;
    }

    startOfToken = nextCheckToken;

    // 문자열 토큰 처리
    if (*nextCheckToken == '"') {
        nextCheckToken++;  // 첫 번째 "를 건너뛰기
        startOfToken = nextCheckToken;
        while (*nextCheckToken != '"' && *nextCheckToken != '\0') {
            nextCheckToken++;
        }
        if (*nextCheckToken == '"') {
            *nextCheckToken = '\0';
            nextCheckToken++;
        }
        return startOfToken;
    }

    // 주석 토큰 처리
    if (*nextCheckToken == '/' && *(nextCheckToken + 1) == '*') {
        startOfToken = nextCheckToken;
        nextCheckToken += 2;  // "/*"를 건너뛰기
        while (!(*nextCheckToken == '*' && *(nextCheckToken + 1) == '/') && *nextCheckToken != '\0') {
            nextCheckToken++;
        }
        if (*nextCheckToken == '*' && *(nextCheckToken + 1) == '/') {
            nextCheckToken += 2;  // "*/"를 건너뛰기
        }
        *nextCheckToken = '\0';  // 주석의 끝을 표시
        return startOfToken;
    }

    // 구분자나 널이 될 때까지, 즉 토큰 끝까지 이동
    while (*nextCheckToken != ' ' && *nextCheckToken != ';' && *nextCheckToken != '\0') {
        nextCheckToken++;
    }
    if (*nextCheckToken == ' ') {
        *nextCheckToken = '\0';
        nextCheckToken++;
        // 중복된 공백 넘어가기
        while (*nextCheckToken == ' ') {
            nextCheckToken++;
        }
    } else if (*nextCheckToken == ';') {
        *nextCheckToken = '\0';
        nextCheckToken++;
        while (*nextCheckToken == ';') {
            nextCheckToken++;
        }
        ExistSemiColons = true; // 10; 토큰에서 세미콜론 검출시 True로 전환 후, 다음 토큰 분리 때 세미콜론 반환
    } else if (*nextCheckToken == '\0') {
        //문장의 끝 도달 NULL을 반환함. 즉, 하나의 라인에서 더 이상 Tokenization를 수행하지 않음.
        nextCheckToken = NULL;
    }
    return startOfToken;
}

