/* 작성자 : 컴퓨터공학과 3학년 김태희(20201101), 조희원(20201086)
 * 작성일자 : 2024/05/19
 * 코드에 대한 설명: 코드의 가독성을 높이기 위한 매크로 사용
 * */


#ifndef LEXICALANALYZER_FSMBYLINE_H
#define LEXICALANALYZER_FSMBYLINE_H
#define DIGIT 0
#define DOT 1
#define UNKNOWN 255

int lineCheck(char* line);
int isDigit(char ch);
int isDot(char ch);
int checkChar(char ch);

#endif //LEXICALANALYZER_FSMBYLINE_H
