/* 작성자 : 컴퓨터공학과 3학년 김태희(20201101), 조희원(20201086)
 * 작성일자 : 2024/05/19
 * 코드에 대한 설명: 부호와 지수가 없는 실수형(정수까지 포함) 상수를 인식하는 어휘 분석기 코드이다.
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
#define MAX_LENGTH 150

void printHeader(FILE *outfp, int maxLen);
char *tokenClassifier(int state);

int main(void) {
    // 입출력 파일의 path
    const char* inputFile = "/Users/neverthe1ess/CLionProjects/LexicalAnalyzer/input.txt";
    const char* outputFile = "/Users/neverthe1ess/CLionProjects/LexicalAnalyzer/output.txt";

    // 입력 받은 문자열 및 최종 상태를 저장하는 배열
    char inputLines[MAX_LINES][MAX_LENGTH];
    char tokens[MAX_LINES][MAX_LENGTH][MAX_LENGTH]; // 토큰을 저장할 배열 추가
    int tokenStates[MAX_LINES][MAX_LENGTH];
    int lineCount = 0;

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

    char* linePtr[MAX_LINES];
    char* token;
    int tokenCount[lineCount]; // 줄 마다의 토큰 개수
    int totalTokenCount = 0; // 총 토큰 개수

    for(int i = 0; i < lineCount; i++){
        linePtr[i] = inputLines[i];
        int j = 0;

        //한 줄마다 토큰 단위로 쪼개기
        token = lineTokenizer(linePtr[i]);
        while(token != NULL) {
            strcpy(tokens[i][j], token); // 토큰 저장
            tokenStates[i][j++] = lineCheck(token);
            token = lineTokenizer(NULL);
        }
        tokenCount[i] = j; //토큰 갯수 넣기
        totalTokenCount += j; // 개수 누적
    }


    /* 파일 쓰기(저장) */
    FILE* outfp = fopen(outputFile, "w");
    if(!outfp) {
        perror("파일 저장에 실패하였습니다. 오류 메시지 ");
        exit(-1);
    }

    /* 표 형식으로 정렬하기 위해 입력값의 최대 길이 찾기, 20으로 초기값을 둠
     * 20을 넘으면 최대 길이에 맞춰서 가로 길이 확장 */
    int maxLen = 13;
//    for (int i = 0; i < lineCount; i++){
//        int testLen = strlen(linePtr[i]);
//        if(maxLen < testLen) {
//            maxLen = testLen;
//        }
//    }

    // 표 머리글(Result, Token, Attribute) 출력 및 저장
    printHeader(outfp, maxLen);
    printHeader(stdout, maxLen);


    char *attribute;
    // 표 데이터(실제 결과) 출력 및 저장, printBody
    for(int i = 0; i < lineCount; i++){
        for(int j = 0; j < tokenCount[i]; j++){ // accept state
            attribute = tokenClassifier(tokenStates[i][j]);
            fprintf(outfp, "%-*s | %s \n", maxLen, tokens[i][j], attribute);
            fprintf(stdout, "%-*s | %s \n", maxLen, tokens[i][j], attribute);
        }
    }

    fclose(outfp);
    return 0;
}

/* 표 머리글 저장 및 결과를 표준 출력 하는 함수 */
void printHeader(FILE *outfp, int maxLen) {
    // 머리글
    fprintf(outfp, "Token       ");
    // 20 넘은 만큼 길이 확장
    for(int i = 0; i < maxLen - 20; i++){
        fprintf(outfp, " ");
    }
    fprintf(outfp, "  | Attribute \n");
    // 20 넘은 만큼 길이 확장
    for(int i = 0; i < maxLen - 20; i++){
        fprintf(outfp, "-");
    }
    // 머리글과 데이터를 구분하는 테두리
    fprintf(outfp, "--------------+-----------\n");

}

char *tokenClassifier(int state){
    if(state >= 290){
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
    } else {
        return "Unknown";
    }
}