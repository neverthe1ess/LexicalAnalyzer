/* 작성자 : 컴퓨터공학과 3학년 김태희(20201101), 조희원(20201086)
 * 작성일자 : 2024/05/19
 * 코드에 대한 설명: 이 코드는 메인 함수에서 한 줄 단위로 입력받아 유한 상태 기계에서
 * 입력받은 기호의 클래스(범주)에 따라 상태 전이를 수행후 최종 상태를 반환한다.
 * */

#include <stdio.h>
#include "fsmbyToken.h"

/* lineCheck()
 * 한 줄 단위(line by line)로 입력받아 FSM에서 상태 전이를 수행한다.
 * 줄의 마지막에 도달하면 최종 상태를 반환한다.  */

int lineCheck(char* line){
        char *ch = line; // main 함수에 넘겨받은 하나의 라인
        int state = START; // start state

        /* FSM에서 입력값에 따라 상태 전이 수행, 단, 유효하지 않은 입력값이 들어오면 -1이라는 거부 상태로 전이(가상 상태) */
        while(*ch != '\0' && state != REJECT){
            int charClass = checkChar(*ch); // 글자 하나씩 클래스 분류(DIGIT, DOT, UNKNOWN)
            switch (state) {
                case START:
                    if(charClass == PLUS_SIGN || charClass == MINUS_SIGN) {
                        state = ADD_SUB_OP1;
                    } else if (charClass == DIGIT) {
                        state = N1;
                    } else if (charClass == LETTERNOTRVS){
                        state = ID1;
                    } else if (charClass == MUL_SIGN){
                        state = MUL_OP2;
                    } else if (charClass == DIV_SIGN ){
                        state = DIV_OP3;
                    } else {
                        state = REJECT;
                    }
                    break;
                case ADD_SUB_OP1:
                    if(charClass == DIGIT){
                        state = N1;
                    } else {
                        state = REJECT;
                    }
                    break;
                case N1:
                    if(charClass == DIGIT){
                        state = N1;
                    } else if (charClass == DOT) {
                        state = N2;
                    } else {
                        state = REJECT;
                    }
                    break;
                case N2:
                    if(charClass == DIGIT){
                        state = CONST_N3;
                    } else {
                        state = REJECT;
                    }
                    break;
                case CONST_N3:
                    if(charClass == DIGIT){
                        state = CONST_N3;
                    } else {
                        state = REJECT;
                    }
                    break;
                case ID1:
                    if(charClass == LETTER || charClass == DIGIT){
                        state = ID1;
                    } else {
                        state = REJECT;
                    }
                    break;
                case MUL_OP2:
                    state = REJECT;
                    break;
                case DIV_OP3:
                    if(charClass == MUL_SIGN){
                        state = CO3;
                    } else {
                        state = REJECT;
                    }
                    break;
                case CO3:
                    if(charClass == MUL_SIGN){
                        state = CO4;
                    } else {
                        state = CO3;
                    } // 오토마타 체크 요망
                    break;
                case CO4:
                    if(charClass == DIV_SIGN){
                        state = CONST_C05;
                    } else {
                        state = CO4;
                    }
                    break;
                case CONST_C05:
                    state = REJECT;
                    break;
            }
            ch++;
        }
        return state; // 최종 state 반환
}

/* Determine Character Class, 가독성을 높이기 위해서 별도의 함수로 한번 더 분리, 결정된 char class를 반환한다. */
int checkChar(char ch){
    if(isDigit(ch)){
        return DIGIT;
    } else if(isDot(ch)){
        return DOT;
    } else if(isPlus(ch)) {
        return PLUS_SIGN;
    } else if(isMinus(ch)){
        return MINUS_SIGN;
    } else if(isMultiply(ch)){
        return MUL_SIGN;
    } else if(isDivision(ch)){
        return DIV_SIGN;
    } else if(isLetter(ch)){
        return LETTER;
    } else if(isLetNotRsrved(ch)){
        return LETTERNOTRVS;
    } else {
        return UNKNOWN;
    }
}

/* 입력받은 문자형 리터럴 값을 아스키코드를 이용해 '0'(48) ~ '9'(57) 정수 판별 */
int isDigit(char ch){
    return (ch >= '0' && ch <= '9');
}

int isDot(char ch){
    return (ch == '.');
}

int isPlus(char ch){
    return (ch == '+');
}

int isMinus(char ch){
    return (ch == '-');
}

int isMultiply(char ch){
    return (ch == '*');
}

int isDivision(char ch){
    return (ch == '/');
}

int isLetter(char ch){
    return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));
}

int isLetNotRsrved(char ch){
    return (ch == 'i' || ch == 'f' || ch == 's' || ch == 'l' || ch == 'd');
}

