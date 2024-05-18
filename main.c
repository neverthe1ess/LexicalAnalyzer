#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fsmbyLine.h"
#define MAX_LINES 100
#define MAX_LENGTH 100


int main(void) {
    const char* inputFile = "/Users/neverthe1ess/CLionProjects/LexicalAnalyzer/input.txt";
    const char* outputFile = "/Users/neverthe1ess/CLionProjects/LexicalAnalyzer/output.txt";
    char inputLines[MAX_LINES][MAX_LENGTH];
    int tokenStates[MAX_LINES];
    int lineCount = 0;

    FILE* infp = fopen(inputFile, "r");
    if(!infp) {
        perror("파일 열기에 실패하였습니다. 오류 메시지 ");
        exit(-1);
    }

    // 한 라인씩 개행 문자까지 읽어서 문자열 배열에 저장, 다 읽으면 fgets는 NULL을 반환하여 루프 종료
    while(fgets(inputLines[lineCount], MAX_LENGTH, infp) && lineCount < MAX_LINES){
        // 불필요한 개행 문자 제거
        inputLines[lineCount][strlen(inputLines[lineCount]) - 1] = '\0';
        lineCount++;
    }
    fclose(infp);

    // 자료형을 맞춰주기 위한 코드
    char* linePtr[MAX_LINES];
    for(int i = 0; i < lineCount; i++){
        linePtr[i] = inputLines[i];
        //한줄 마다 어휘 분석 수행
        tokenStates[i] = lineCheck(linePtr[i], lineCount); // 한줄 단위 넣기
        //printf("%d\n", tokenStates[i]);
    }


    /* 저장 코드 */
    FILE* outfp = fopen(outputFile, "w");
    if(!outfp) {
        perror("파일 저장에 실패하였습니다. 오류 메시지 ");
        exit(-1);
    }

    // 간판 저장 및 표준 입출력
    fprintf(outfp, "Result | \t Token\t\t\t | Attribute \n");
    fprintf(stdout, "Result | \t Token\t\t\t | Attribute \n");
    fprintf(outfp, "-------+---------------------+---------\n");
    fprintf(stdout, "-------+---------------------+---------\n");

    // 예쁘게 표 형식으로 정렬하기 위해 가장 긴 입력값의 길이 찾기
    int maxLen = -1;
    for (int i = 0; i < lineCount; i++){
        int testLen = strlen(linePtr[i]);
        if(maxLen < testLen) {
            maxLen = testLen;
        }
    }
    // 파일 및 표준 입출력
    for(int i = 0; i < lineCount; i++){
        if(tokenStates[i] == 1 || tokenStates[i] == 3){
            fprintf(outfp, "accept | %-*s | constant \n", maxLen, linePtr[i]);
            fprintf(stdout, "accept | %-*s | constant \n", maxLen, linePtr[i]);
        } else {
            fprintf(outfp, "accept | %-*s | constant \n", maxLen, linePtr[i]);
            fprintf(stdout, "reject | %-*s | unknown \n", maxLen, linePtr[i]);
        }
    }


    return 0;

}
