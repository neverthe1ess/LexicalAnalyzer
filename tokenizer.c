/* 작성자 : 컴퓨터공학과 3학년 김태희(20201101), 조희원(20201086)
 * 작성일자 : 2024/05/26
 * 코드에 대한 설명: 이 코드는 메인 함수에서 한 줄 단위로 입력받아 의미가 있는 단위인 토큰 단위를 쪼개는 기능을 수행함.
 * */

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include "tokenizer.h"

static bool existQuotationSymbol = false; // TokenState1, 함수 분리를 위해 전역 정적 변수
static bool existCommentSymbol = false; // TokenState2, 함수 분리를 위해 전역 정적 변수

char *generalTokenizer(char *line) {
    static char *nextCheckToken = NULL;  // static 변수로 함수가 다시 호출되어도 호출될때 초기화 되지 않음.
    static bool existSemiColons = false; // 10; 붙어 있는 세미콜론 제거를 위한 변수, 10;  토큰 검사시 True 전환
    static bool stringStart = false;

    char *startOfToken;

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

    // 주석 기호나 문자열 따옴표 기호가 아닌 일반 심볼일 때
    if(isGeneralSymbol()){
        // 구분자나 주석기호, 따옴표, 널이 될 때까지, 즉 토큰 끝까지 이동
        while (*nextCheckToken != ' ' && *nextCheckToken != ';' && *nextCheckToken != '\n' && *nextCheckToken != '\0') {
            // 주석 기호 탐지 시
            if(*nextCheckToken == '/' && *(nextCheckToken + 1) == '*'){
                existCommentSymbol = true;
                nextCheckToken += 2; // 주석의 시작을 넘기기
                break;
            } else if (*nextCheckToken == '"'){ //stringstart 아직 구현 안함
                existQuotationSymbol = true;
                nextCheckToken++;
                break;
            }
            nextCheckToken++;
        } if (*nextCheckToken == ' ' && isGeneralSymbol()) {
            *nextCheckToken = '\0';
            nextCheckToken++;
            // 중복된 공백 넘어가기
            while (*nextCheckToken == ' ') {
                nextCheckToken++;
            }
        } else if (*nextCheckToken == ';' && isGeneralSymbol()) {
            *nextCheckToken = '\0';
            nextCheckToken++;
            while (*nextCheckToken == ';') {
                nextCheckToken++;
            }
            existSemiColons = true; // 10; 토큰에서 세미콜론 검출시 True로 전환 후, 다음 토큰 분리 때 세미콜론 반환
        } else if(*nextCheckToken == '\n' && isGeneralSymbol()){
            *nextCheckToken = '\0';
            nextCheckToken++;
            while (*nextCheckToken == '\n') {
                nextCheckToken++;
            }
        } else if (*nextCheckToken == '\0' && isGeneralSymbol()) {
            //문장의 끝 도달 NULL을 반환함. 즉, 하나의 라인에서 더 이상 Tokenization를 수행하지 않음.
            nextCheckToken = NULL;
        }
    }
    // 주석 기호 검출 시
    if(existCommentSymbol == true){ // 얘도 세미콜론 로직과 비슷하게 구현하자 .
        while (*nextCheckToken != '\0') {
            if (*nextCheckToken == '*' && *(nextCheckToken + 1) == '/') {
                existCommentSymbol = false;
                nextCheckToken += 2; // 주석의 끝을 넘기기
                *nextCheckToken = '\0';
                nextCheckToken++;
                break;
            }
            nextCheckToken++;
        }
    }

    if(existQuotationSymbol == true){
        while(*nextCheckToken != '\0'){
            if(*nextCheckToken == '"'){
                existQuotationSymbol = false;
                nextCheckToken++;
                *nextCheckToken = '\0';
                break;
            }
            nextCheckToken++;
        }
    }

    return startOfToken;
}

bool isGeneralSymbol() {
    return existCommentSymbol == false && existQuotationSymbol == false;
}

