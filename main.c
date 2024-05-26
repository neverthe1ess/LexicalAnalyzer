/* 작성자 : 컴퓨터공학과 3학년 김태희(20201101), 조희원(20201086)
 * 작성일자 : 2024/05/26
 * 코드에 대한 설명: 여러 요구사항을 만족하는 어휘 분석기 코드임.
 * 수행 순서:
 * 1. 지정된 입출력 파일 path에 따라 파일을 읽고 2차원 배열에 저장한다.
 * 2. 2차원 배열에 저장된 입력값을 한 줄씩 FSM 함수(linecheck)를 호출하여 수행한다.
 * 3. FSM 함수의 리턴 값으로 최종 상태를 받아서 수락 상태인지 거부 상태인지 확인한다.
 * 4. 수락 상태 여부와 입력값, 토큰의 클래스를 출력 및 지정한 파일에 저장한다.
 * */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fsmbyToken.h"
#include "tokenizer.h"
#define MAX_LINES 100
#define MAX_LENGTH 300
#define MAX_TOKENS 1000

void printHeader(FILE *outfp, int maxLen);
char *tokenClassifier(int state);
int isDuplicate(char tokens[][MAX_LENGTH], int tokenCount, char *token);

int main(void) {
    // 입출력 파일의 path
    const char* inputFile = "/Users/neverthe1ess/CLionProjects/LexicalAnalyzer/input.txt";
    const char* outputFile = "/Users/neverthe1ess/CLionProjects/LexicalAnalyzer/output.txt";

    // 입력 받은 문자열 및 최종 상태를 저장하는 배열
    char inputLines[MAX_LINES][MAX_LENGTH];
    char tokens[MAX_TOKENS][MAX_LENGTH]; // 모든 토큰을 저장할 배열 추가
    int tokenStates[MAX_TOKENS]; // 토큰의 상태를 저장할 배열
    int lineCount = 0;
    int totalTokenCount = 0; // 전체 토큰 개수

    /* 파일 읽기 */
    FILE* infp = fopen(inputFile, "r");
    if(!infp) {
        perror("파일 열기에 실패하였습니다. 오류 메시지 ");
        exit(-1);
    }

    // 한 라인씩 개행 문자까지 읽어서 문자열 배열에 저장, 다 읽으면 fgets는 NULL을 반환하여 루프 종료
    while(fgets(inputLines[lineCount], MAX_LENGTH, infp) && lineCount < MAX_LINES){
        // 어휘 분석 시 방해가 되는 개행 문자 제거
        if(inputLines[lineCount][strlen(inputLines[lineCount]) - 1] == '\n'){
            inputLines[lineCount][strlen(inputLines[lineCount]) - 1] = '\0';
        }
        lineCount++;
    }
    fclose(infp);


    char* token;
    for(int i = 0; i < lineCount; i++){
        // 한 줄마다 토큰 단위로 쪼개기
        token = generalTokenizer(inputLines[i]);
        while(token != NULL) {
            if(!isDuplicate(tokens, totalTokenCount, token)) {
                strcpy(tokens[totalTokenCount], token); // 토큰 저장
                tokenStates[totalTokenCount++] = lineCheck(token);
            }
            token = generalTokenizer(NULL);
        }
    }

    /* 파일 쓰기(저장) */
    FILE* outfp = fopen(outputFile, "w");
    if(!outfp) {
        perror("파일 저장에 실패하였습니다. 오류 메시지 ");
        exit(-1);
    }

    /* 표 형식으로 정렬하기 위해 입력값의 최대 길이 찾기 */
    int maxLen = 15; // 매직넘버 10, 표 출력 시 알맞은 길이로 기본 설정
    for (int i = 0; i < totalTokenCount; i++){
        int testLen = strlen(tokens[i]);
        if(maxLen < testLen) {
            maxLen = testLen;
        }
    }

    // 표 머리글(Result, Token, Attribute) 출력 및 저장
    printHeader(outfp, maxLen);
    printHeader(stdout, maxLen);

    char *attribute;
    // 표 데이터(실제 결과) 출력 및 저장, printBody
    for(int i = 0; i < totalTokenCount; i++){
        attribute = tokenClassifier(tokenStates[i]);
        fprintf(outfp, "%-*s | %s \n", maxLen, tokens[i], attribute);
        fprintf(stdout, "%-*s | %s \n", maxLen, tokens[i], attribute);
    }

    fclose(outfp);
    return 0;
}

/* 표 머리글 저장 및 결과를 표준 출력 하는 함수 */
void printHeader(FILE *outfp, int maxLen) {
    // 머리글
    fprintf(outfp, "Token       ");
    // 최대 길이만큼 길이 확장
    for(int i = 0; i < maxLen - 15; i++){
        fprintf(outfp, " ");
    }
    fprintf(outfp, "    | Attribute \n");
    // 최대 길이만큼 길이 확장
    for(int i = 0; i < maxLen - 15; i++){
        fprintf(outfp, "-");
    }
    // 머리글과 데이터를 구분하는 테두리
    fprintf(outfp, "----------------+-----------\n");

}
/* 최종 상태에 따른 토큰의 Attribute 분류 */
char *tokenClassifier(int state){
    if(state >= REJECT){
        return "Unknown";
    } else if (state >= DATATYPE){
        return "DataType";
    } else if (state >= IDENTIFIER){
        return "Identifier";
    } else if (state >= CONST){
        return "Constant";
    } else if (state >= OPERATOR){
        return "Operator";
    } else if (state >= DELIMITER){
        return "Delimiter";
    } else if (state >= STRING) {
        return "String";
    } else if (state >= COMMENTS) {
        return "Comments";
    } else {
        return "UnKnown";
    }
}

/* 토큰이 중복인지 확인하는 함수 */
int isDuplicate(char tokens[][MAX_LENGTH], int tokenCount, char *token) {
    for(int i = 0; i < tokenCount; i++) {
        if(strcmp(tokens[i], token) == 0) {
            return 1; // 중복
        }
    }
    return 0; // 중복 아님
}
