/* 작성자 : 컴퓨터공학과 3학년 김태희(20201101), 조희원(20201086)
 * 작성일자 : 2024/05/26
 * 코드에 대한 설명: 이 코드는 메인 함수에서 한 줄 단위로 입력받아 의미가 있는 단위인 토큰 단위를 쪼개는 기능을 수행함.
 * */

#include <stddef.h>
#include "tokenizer.h"

char *lineTokenizer(char *line) {
    static char* nextCheckToken = NULL;  // static 변수로 함수가 다시 호출되어도 호출될때 초기화 되지 않음.
    static int ExistSemiColons = 0;
    char *startOfToken;

    if(ExistSemiColons){
        ExistSemiColons = 0;
        return ";";
    }

    if(line != NULL) { // 새로운 문장 진입
        nextCheckToken = line;
    }

    // 문장의 끝, 더 이상 반환할 토큰이 없음.
    if(nextCheckToken == NULL || *nextCheckToken == '\0'){
        return NULL;
    }

    startOfToken = nextCheckToken;

    // 구분자나 널이 될 때까지, 즉 토큰 끝까지 이동
    while(*nextCheckToken != ' ' && *nextCheckToken != ';' && *nextCheckToken != '\0') {
        nextCheckToken++;
    }

    if(*nextCheckToken == ' ') {
        *nextCheckToken = '\0';
        nextCheckToken++;
        // 중복된 공백 넘어가기
        while(*nextCheckToken == ' '){
            nextCheckToken++;
        }
    } else if(*nextCheckToken == ';'){
        *nextCheckToken = '\0';
        nextCheckToken++;
        while(*nextCheckToken == ';'){
            nextCheckToken++;
        }
        ExistSemiColons = 1;
    } else if(*nextCheckToken == '\0'){
        //문장의 끝 도달 NULL을 반환함. 즉, 하나의 라인에서 더 이상 Tokenization를 수행하지 않음.
        nextCheckToken = NULL;
    }
    return startOfToken;
}

