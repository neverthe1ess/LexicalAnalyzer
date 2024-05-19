///* 작성자 : 컴퓨터공학과 3학년 김태희(20201101), 조희원(20201086)
// * 작성일자 : 2024/05/19
// * 코드에 대한 설명: 부호와 지수가 없는 실수형(정수까지 포함) 상수를 인식하는 어휘 분석기 코드이다. 수정수정
// *
// * */
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include "fsmbyLine.h"
//#define MAX_LINES 100
//#define MAX_LENGTH 100
//
//int main(void) {
//    // 입출력 파일의 path
//    const char* inputFile = "/Users/neverthe1ess/CLionProjects/LexicalAnalyzer/input.txt";
//    const char* outputFile = "/Users/neverthe1ess/CLionProjects/LexicalAnalyzer/output.txt";
//    // 입력 받은 문자열 및 최종 상태를 저장하는 배열
//    char inputLines[MAX_LINES][MAX_LENGTH];
//    int tokenStates[MAX_LINES];
//    int lineCount = 0;
//
//    /* 파일 읽기 */
//    FILE* infp = fopen(inputFile, "r");
//    if(!infp) {
//        perror("파일 열기에 실패하였습니다. 오류 메시지 ");
//        exit(-1);
//    }
//
//    // 한 라인씩 개행 문자까지 읽어서 문자열 배열에 저장, 다 읽으면 fgets는 NULL을 반환하여 루프 종료
//    while(fgets(inputLines[lineCount], MAX_LENGTH, infp) && lineCount < MAX_LINES){
//        // 어휘 분석 시 방해가 되는 개행 문자 제거
//        if(inputLines[lineCount][strlen(inputLines[lineCount]) - 1] == '\n'){
//            inputLines[lineCount][strlen(inputLines[lineCount]) - 1] = '\0';
//        }
//        lineCount++;
//    }
//    fclose(infp);
//
//    char* linePtr[MAX_LINES];
//    for(int i = 0; i < lineCount; i++){
//        linePtr[i] = inputLines[i];
//        //한줄 마다 어휘 분석 수행
//        tokenStates[i] = lineCheck(linePtr[i]);
//    }
//
//    /* 파일 쓰기(저장) */
//    FILE* outfp = fopen(outputFile, "w");
//    if(!outfp) {
//        perror("파일 저장에 실패하였습니다. 오류 메시지 ");
//        exit(-1);
//    }
//
//    /* 예쁘게 표 형식으로 정렬하기 위해 가장 긴 입력값의 길이 찾기 */
//    int maxLen = 20;
//    for (int i = 0; i < lineCount; i++){
//        int testLen = strlen(linePtr[i]);
//        if(maxLen < testLen) {
//            maxLen = testLen;
//        }
//    }
//
//    // 간판 저장 및 표준 입출력
//    fprintf(outfp, "Result | Token\t\t\t\t  | Attribute \n");
//    fprintf(stdout, "Result | Token\t\t\t\t  | Attribute \n");
//    fprintf(outfp, "-------+----------------------+-----------\n");
//    fprintf(stdout, "-------+----------------------+-----------\n");
//
//    // 파일 및 표준 입출력
//    for(int i = 0; i < lineCount; i++){
//        if(tokenStates[i] == 1 || tokenStates[i] == 3){ // accept state,
//            fprintf(outfp, "accept | %-*s | constant \n", maxLen, linePtr[i]);
//            fprintf(stdout, "accept | %-*s | constant \n", maxLen, linePtr[i]);
//        } else {
//            fprintf(outfp, "reject | %-*s | unknown \n", maxLen, linePtr[i]);
//            fprintf(stdout, "reject | %-*s | unknown \n", maxLen, linePtr[i]);
//        }
//    }
//
//    fclose(outfp);
//    return 0;
//}
