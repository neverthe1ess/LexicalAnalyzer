/* 작성자 : 컴퓨터공학과 3학년 김태희(20201101), 조희원(20201086)
 * 작성일자 : 2024/05/28
 * 코드에 대한 설명: 코드의 가독성을 높이기 위한 매크로 사용, 보고서의 오토마타 상태 번호와 매핑시켰음.
 * */
#ifndef LEXICALANALYZER_FSMBYTOKEN_H
#define LEXICALANALYZER_FSMBYTOKEN_H

// symbol
#define DIGIT 10
#define DOT 11
#define LETTER 12
#define PLUS_SIGN 14
#define MINUS_SIGN 15
#define MUL_SIGN 16
#define DIV_SIGN 17
#define ASSIGN_DELIM 18
#define SEMICOLON_DELIM 19
#define STRING_SIGN 20
#define UNKNOWN 355

// state
#define START 0

//Comments
#define COMMENTS 60
#define COMM_C05 61

//String
#define STRING 70
#define STR2 72

//delimiter
#define DELIMITER 80
#define DE1 81


// operator
#define OPERATOR 100
#define ADD_SUB_OP1 101
#define MUL_OP2 102
#define DIV_OP3 103

// constant
#define CONST 110
#define CONST_N1 111
#define CONST_N3 113


// identifer
#define IDENTIFIER 120
#define ID1 121

#define ID_D01 141
#define ID_D02 142
#define ID_D03 143
#define ID_D04 144

#define ID_D11 151

#define ID_D21 161
#define ID_D22 162
#define ID_D23 163

#define ID_D31 171
#define ID_D32 172
#define ID_D33 173
#define ID_D34 174
#define ID_D35 175

#define ID_D41 181
#define ID_D42 182
#define ID_D43 183

// DataType
#define DATATYPE 190
#define DATATYPE_D99 199

// 최종적으로 Reject state
#define REJECT 290
#define N2 292
#define CO3 293
#define CO4 294
#define STR1 295

int lineCheck(char* token);
int isDigit(char ch);
int isDot(char ch);
int isPlus(char ch);
int isMinus(char ch);
int isMultiply(char ch);
int isDivision(char ch);
int isLetter(char ch);
int checkChar(char ch);
int isAssign(char ch);
int isSemiColon(char ch);
int isStringSign(char ch);

#endif //LEXICALANALYZER_FSMBYTOKEN_H
