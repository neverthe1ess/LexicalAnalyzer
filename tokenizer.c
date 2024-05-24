#include <stddef.h>
#include "tokenizer.h"

char *lineTokenizer(char *line) {
    static char* nextCheckToken = NULL;
    char *startOfToken;

    if(line != NULL) { // 새로운 문장 진입
        nextCheckToken = line;
    }

    // 문장의 끝, 더 이상 반환할 토큰이 없음.
    if(nextCheckToken == NULL || *nextCheckToken == '\0'){
        return NULL;
    }

    startOfToken = nextCheckToken;

    // 구분자인 공백이나 널이 될 때까지, 즉 토큰 끝까지 이동
    while(*nextCheckToken != ' ' && *nextCheckToken != '\0') {
        nextCheckToken++;
    }

    if(*nextCheckToken == ' ') {
        *nextCheckToken = '\0';
        nextCheckToken++;
        // 중복된 공백 넘어가기
        while(*nextCheckToken == ' '){
            nextCheckToken++;
        }

    } else if(*nextCheckToken == '\0'){
        nextCheckToken = NULL;
    }

    return startOfToken;
}

