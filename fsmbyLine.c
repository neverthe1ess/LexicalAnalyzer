#include "fsmbyLine.h"

int lineCheck(char* lines, int lineCount){
        char *ch = lines;
        int state = 0; // start state
        while(*ch != '\0' && state != -1){
            switch (state) {
                case 0:
                    if(isDigit(*ch)){
                        state = 1;
                    } else if (isDot(*ch)){
                        state = 2;
                    } else {
                        state = -1;
                    }
                    break;
                case 1:
                    if(isDigit(*ch)){
                        state = 1;
                    } else if(isDot(*ch)){
                        state = 2;
                    } else {
                        state = -1;
                    }
                    break;
                case 2:
                    if (isDigit(*ch)) {
                        state = 3;
                    } else {
                        state = -1;
                    }
                case 3:
                    if(!isDigit(*ch)){
                        state = -1;
                    }
                    break;
                default:
                    break;
            }
            ch++;
        }
        return state; // 최종 state 반환
}

int isDigit(char ch){
    if (ch >= '0' && ch <= '9') {
        return 1;
    } else {
        return 0;
    }
}

int isDot(char ch){
    if (ch == '.'){
        return 1;
    } else{
        return 0;
    }
}


// character class determine 함수 만들기



//int lex(char *line){
//
//}