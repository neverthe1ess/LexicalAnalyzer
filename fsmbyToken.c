/* 작성자 : 컴퓨터공학과 3학년 김태희(20201101), 조희원(20201086)
 * 작성일자 : 2024/05/26
 * 코드에 대한 설명: 이 코드는 메인 함수에서 Tokenization을 수행한 토큰 단위로 입력받아
 * 유한 상태 기계에서 입력받은 기호의 클래스(범주)에 따라 상태 전이를 수행후 최종 상태를 반환한다.
 * */

#include "fsmbyToken.h"
#include <stdio.h>

/* lineCheck()
 * 토큰 단위로 입력받아 FSM에서 상태 전이를 수행한다.
 * 줄의 마지막에 도달하면 최종 상태를 반환한다.  */

int lineCheck(char* token){
    char *ch = token; // main 함수에서 넘겨받은 하나의 토큰
    int state = START;

    /* FSM에서 입력값에 따라 상태 전이 수행, 단, 유효하지 않은 입력값이 들어오면 REJECT라는 거부 상태로 전이(가상 상태) */
    while(*ch != '\0' && state != REJECT){
        int charClass = checkChar(*ch); // 글자 하나씩 클래스 분류(DIGIT, DOT, UNKNOWN, ...)
        switch (state) {
            case START:
                if(charClass == PLUS_SIGN || charClass == MINUS_SIGN) {
                    state = ADD_SUB_OP1;
                } else if (charClass == DIGIT) {
                    state = CONST_N1;
                } else if (charClass == MUL_SIGN){
                    state = MUL_OP2;
                } else if (charClass == DIV_SIGN){
                    state = DIV_OP3;
                } else if (*ch == 'f'){ // float
                    state = ID_D01;
                } else if (*ch == 'i'){ // int
                    state = ID_D11;
                } else if (*ch == 's'){ // short
                    state = ID_D21;
                } else if (*ch == 'd'){ // double
                    state = ID_D31;
                } else if (*ch == 'l'){ // long
                    state = ID_D41;
                } else if (charClass == LETTER){ // Alphabet - {f, i, s, d, l}
                    state = ID1;
                } else if (charClass == ASSIGN_DELIM || charClass == SEMICOLON_DELIM){
                    state = DE1;
                } else if (charClass == STRING_SIGN){
                    state = STR1;
                } else {
                    state = REJECT;
                }
                break;
            case ADD_SUB_OP1:
                if(charClass == DIGIT){
                    state = CONST_N1;
                } else {
                    state = REJECT;
                }
                break;
            case CONST_N1:
                if(charClass == DIGIT){
                    state = CONST_N1;
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
                } else { // NOT MUL SIGN
                    state = CO3;
                } // 오토마타 체크 요망
                break;
            case CO4:
                if(charClass == DIV_SIGN){
                    state = COMM_C05;
                } else { // NOT DIV SIGN
                    state = CO3;
                }
                break;
            case COMM_C05:
                state = REJECT;
                break;

            case ID_D01:
                if(*ch == 'l'){
                    state = ID_D02;
                } else if (charClass == LETTER || charClass == DIGIT && *ch != 'l'){
                    state = ID1;
                } else {
                    state = REJECT;
                }
                break;
            case ID_D02:
                if(*ch == 'o'){
                    state = ID_D03;
                } else if (charClass == LETTER || charClass == DIGIT  && *ch != 'o'){
                    state = ID1;
                } else {
                    state = REJECT;
                }
                break;
            case ID_D03:
                if(*ch == 'a'){
                    state = ID_D04;
                } else if(charClass == LETTER || charClass == DIGIT  && *ch != 'a'){
                    state = ID1;
                } else {
                    state = REJECT;
                }
                break;
            case ID_D04:
                if(*ch == 't'){
                    state = DATATYPE_D99;
                } else {
                    state = REJECT;
                }
                break;
            case ID_D11:
                if(*ch == 'n'){
                    state = ID_D04;
                } else if(charClass == LETTER || charClass == DIGIT  && *ch != 'n'){
                    state = ID1;
                } else {
                    state = REJECT;
                }
                break;
            case ID_D21:
                if(*ch == 'h'){
                    state = ID_D22;
                } else if(charClass == LETTER || charClass == DIGIT  && *ch != 'h'){
                    state = ID1;
                } else {
                    state = REJECT;
                }
                break;
            case ID_D22:
                if(*ch == 'o'){
                    state = ID_D23;
                } else if(charClass == LETTER || charClass == DIGIT  && *ch != 'o'){
                    state = ID1;
                } else {
                    state = REJECT;
                }
                break;
            case ID_D23:
                if(*ch == 'r'){
                    state = ID_D04;
                } else if(charClass == LETTER || charClass == DIGIT  && *ch != 'r'){
                    state = ID1;
                } else {
                    state = REJECT;
                }
                break;
            case ID_D31:
                if(*ch == 'o'){
                    state = ID_D32;
                } else if(charClass == LETTER || charClass == DIGIT  && *ch != 'o'){
                    state = ID1;
                } else {
                    state = REJECT;
                }
                break;
            case ID_D32:
                if(*ch == 'u'){
                    state = ID_D33;
                } else if(charClass == LETTER || charClass == DIGIT  && *ch != 'u'){
                    state = ID1;
                } else {
                    state = REJECT;
                }
                break;
            case ID_D33:
                if(*ch == 'b'){
                    state = ID_D34;
                } else if(charClass == LETTER || charClass == DIGIT  && *ch != 'b'){
                    state = ID1;
                } else {
                    state = REJECT;
                }
                break;
            case ID_D34:
                if(*ch == 'l'){
                    state = ID_D35;
                } else if(charClass == LETTER || charClass == DIGIT  && *ch != 'l'){
                    state = ID1;
                } else {
                    state = REJECT;
                }
                break;
            case ID_D35:
                if(*ch == 'e'){
                    state = DATATYPE_D99;
                } else if(charClass == LETTER || charClass == DIGIT && *ch != 'e'){
                    state = ID1;
                } else {
                    state = REJECT;
                }
                break;
            case ID_D41:
                if(*ch == 'o'){
                    state = ID_D42;
                } else if (charClass == LETTER || charClass == DIGIT  && *ch != 'o'){
                    state = ID1;
                } else {
                    state = REJECT;
                }
                break;
            case ID_D42:
                if(*ch == 'n'){
                    state = ID_D43;
                } else if (charClass == LETTER || charClass == DIGIT  && *ch != 'n'){
                    state = ID1;
                } else {
                    state = REJECT;
                }
                break;
            case ID_D43:
                if(*ch == 'g'){
                    state = DATATYPE_D99;
                } else if(charClass == LETTER || charClass == DIGIT  && *ch != 'g'){
                    state = ID1;
                } else {
                    state = REJECT;
                }
                break;
            case DE1:
                state = REJECT;
                break;
            case DATATYPE_D99:
                if(charClass == LETTER || charClass == DIGIT){
                    state = ID1;
                } else {
                    state = REJECT;
                }
                break;
            case STR1:
                if(charClass == STRING_SIGN){
                    state = STR2;
                } else {
                    state = STR1;
                }
                break;
            case STR2:
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
    } else if(isAssign(ch)){
        return ASSIGN_DELIM;
    } else if(isSemiColon(ch)){
        return SEMICOLON_DELIM;
    } else if(isStringSign(ch)){
        return STRING_SIGN;
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

int isAssign(char ch){
    return (ch == '=');
}

int isSemiColon(char ch){
    return (ch == ';');
}

int isStringSign(char ch){
    return (ch == '"');
}