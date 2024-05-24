/* 작성자 : 컴퓨터공학과 3학년 김태희(20201101), 조희원(20201086)
 * 작성일자 : 2024/05/19
 * 코드에 대한 설명: 코드의 가독성을 높이기 위한 매크로 사용
 * */


#ifndef LEXICALANALYZER_FSMBYTOKEN_H
#define LEXICALANALYZER_FSMBYTOKEN_H
#define DIGIT 10
#define DOT 11
#define LETTER 12
#define LETTERNOTRVS 13
#define PLUS_SIGN 14
#define MINUS_SIGN 15
#define MUL_SIGN 16
#define DIV_SIGN 17


#define START 0


#define ADD_SUB_OP1 101
#define N1 102
#define N2 103
#define CONST_N3 104

#define ID1 111

#define MUL_OP2 121

#define DIV_OP3 131
#define CO3 132
#define CO4 133
#define CONST_C05 134


#define REJECT 199
#define UNKNOWN 255

int lineCheck(char* line);
int isDigit(char ch);
int isDot(char ch);
int isPlus(char ch);
int isMinus(char ch);
int isMultiply(char ch);
int isDivision(char ch);
int isLetNotRsrved(char ch);
int isLetter(char ch);
int checkChar(char ch);

#endif //LEXICALANALYZER_FSMBYTOKEN_H
