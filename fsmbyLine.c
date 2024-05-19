/* 작성자 : 컴퓨터공학과 3학년 김태희(20201101), 조희원(20201086)
 * 작성일자 : 2024/05/19
 * 코드에 대한 설명: 이 코드는 메인 함수에서 한 줄 단위로 입력받아 유한 상태 기계에서
 * 입력받은 기호의 클래스(범주)에 따라 상태 전이를 수행후 최종 상태를 반환한다.
 * */

#include "fsmbyLine.h"

/* lineCheck()
 * 한 줄 단위(line by line)로 입력받아 FSM에서 상태 전이를 수행한다.
 * 줄의 마지막에 도달하면 최종 상태를 반환한다.  */

int lineCheck(char* line){
        char *ch = line; // main 함수에 넘겨받은 하나의 라인
        int state = 0; // start state

        /* FSM에서 입력값에 따라 상태 전이 수행, 단, 유효하지 않은 입력값이 들어오면 -1이라는 거부 상태로 전이(가상 상태) */
        while(*ch != '\0' && state != -1){
            int charClass = checkChar(*ch); // 글자 하나씩 클래스 분류(DIGIT, DOT, UNKNOWN)
            switch (state) {
                case 0:
                    if(charClass == DIGIT){   // 입력 알파벳이 0~9 사이면 1로 전이
                        state = 1;
                    } else if (charClass == DOT){  // 입력 알파벳이 .(dot) 이면 2로 전이
                        state = 2;
                    } else {
                        state = -1;     // 입력 알파벳이 유효하지 않은 값이면, -1(reject)로 전이
                    }
                    break;
                case 1:   //accept state
                    if(charClass == DIGIT){
                        state = 1;
                    } else if(charClass == DOT){
                        state = 2;
                    } else {
                        state = -1;
                    }
                    break;
                case 2:
                    if (charClass == DIGIT) {
                        state = 3;
                    } else {
                        state = -1;
                    }
                    break;
                case 3:  // accept state
                    if(charClass != DIGIT){
                        state = -1;
                    }
                    break;
                default:
                    break;
            }
            ch++; // 다음 검사한 글자를 가리키기
        }
        return state; // 최종 state 반환
}

/* Determine Character Class, 가독성을 높이기 위해서 별도의 함수로 한번 더 분리, 결정된 char class를 반환한다. */
int checkChar(char ch){
    if(isDigit(ch)){
        return DIGIT;
    } else if(isDot(ch)){
        return DOT;
    } else {
        return UNKNOWN;
    }
}

/* 입력받은 문자형 리터럴 값을 아스키코드를 이용해 '0'(48) ~ '9'(57) 정수 판별 */
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