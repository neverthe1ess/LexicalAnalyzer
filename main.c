/* 작성자 : 컴퓨터공학과 3학년 조희원(20201086)
 * 작성일자 : 2024/06/06
 * 코드에 대한 설명: 여러 요구사항을 만족하는 어휘 분석기 코드임.
 * 수행 순서:
 * 1. 지정된 입출력 파일 path에 따라 파일을 읽고 문자열(1차원 배열)로 저장한다.
 * 2. 1차원 배열에 저장된 입력값 전체를 FSM 함수(linecheck)를 호출하여 수행한다.
 * 3. FSM 함수의 리턴 값으로 최종 상태를 받아서 수락 상태인지 거부 상태인지 확인한다.
 * 4. 입력값, 토큰의 클래스를 출력 및 지정한 파일에 저장한다.
 * */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "fsmbyToken.h"
#include "tokenizer.h"
#define MAX_LENGTH 1500
#define MAX_LINES 100
#define MAX_LINE_LENGTH 100

void printHeader(FILE *outfp, int maxLen);

int main(void) {
    // 입출력 파일의 path
    const char* inputFile = "/Users/neverthe1ess/CLionProjects/LexicalAnalyzer/input.txt";
    const char* outputFile = "/Users/neverthe1ess/CLionProjects/LexicalAnalyzer/output.txt";

    // 입력 받은 문자열 및 최종 상태를 저장하는 배열
    char inputLines[MAX_LINES][MAX_LINE_LENGTH];
    char resultLines[MAX_LINES][MAX_LINE_LENGTH];
    // 토큰의 상태를 저장할 배열
    int tokenStates[MAX_LINES][MAX_LINE_LENGTH];
    int totalTokenCount = 0; // 전체 토큰 개수
    int lineCount = 0; // 줄의 개수


    /* 파일 읽기 */
    FILE* infp = fopen(inputFile, "r");
    if(!infp) {
        perror("파일 열기에 실패하였습니다. 오류 메시지 ");
        exit(-1);
    }

    /* 한줄 단위로 입력 받기 */
    while (fgets(inputLines[lineCount], MAX_LINE_LENGTH, infp) != NULL) {
        // 어휘 분석 시 방해가 되는 개행 문자 제거
        if(inputLines[lineCount][strlen(inputLines[lineCount]) - 1] == '\n'){
            inputLines[lineCount][strlen(inputLines[lineCount]) - 1] = '\0';
        }
        lineCount++;
    }
    fclose(infp);

    char *linePtr[MAX_LINES];
    int tokenCount[MAX_LINES];
    char* token;

    for (int i = 0; i < lineCount; i++) {
        strcpy(resultLines[i], inputLines[i]); // inputLines는 토큰화로 인해 정상 출력이 안됨. 보조 변수 사용
        linePtr[i] = inputLines[i];
        int j = 0;

        //한 줄마다 토큰 단위로 쪼개기
        token = generalTokenizer(linePtr[i]);
        while (token != NULL) {
            if(lineCheck(token) != START && lineCheck(token) != COMM_C05){
                tokenStates[i][j++] = lineCheck(token);
            }
            token = generalTokenizer(NULL);
        }
        tokenCount[i] = j;
        totalTokenCount += j;
    }

    bool result[MAX_LINES];
    for (int i = 0; i < lineCount; i++) {
        result[i] = parser(tokenStates[i], tokenCount[i]);
    }

    /* 파일 쓰기(저장) */
    FILE* outfp = fopen(outputFile, "w");
    if(!outfp) {
        perror("파일 저장에 실패하였습니다. 오류 메시지 ");
        exit(-1);
    }

    /* 표 형식으로 정렬하기 위해 입력값(lexeme)의 최대 길이 찾기 */
    int maxLen = 15; // 매직넘버 15, 표 출력 시 알맞은 길이로 기본 설정
//    for (int i = 0; i < totalTokenCount; i++){
//        int testLen = strlen(resultLines[i]);
//        if(maxLen < testLen) {
//            maxLen = testLen;
//        }
//    }


    // 표 머리글(Token, Attribute) 출력 및 저장
    printHeader(outfp, maxLen);
    printHeader(stdout, maxLen);

    // 표 데이터(실제 결과) 출력 및 저장, printBody
    for(int i = 0; i < lineCount; i++){
          bool recognizeResult = result[i];
          if(recognizeResult){
              fprintf(outfp, "%-*s | Valid \n", maxLen, resultLines[i]);
              fprintf(stdout, "%-*s | Valid \n", maxLen, resultLines[i]);
          } else {
              fprintf(outfp, "%-*s | Invalid \n", maxLen, resultLines[i]);
              fprintf(stdout, "%-*s | Invalid \n", maxLen, resultLines[i]);
          }

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
