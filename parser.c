#include <stdio.h>
#include "parser.h"

int tokenIndex;
int recognizeGrammar;
int endOfTokenIndex;
int tokens[1000];

bool parser(int token[], int tokenCount){
    recognizeGrammar = true;
    tokenIndex = 0;
    endOfTokenIndex = tokenCount;
    for(int i = 0; i < tokenCount; i++){
        tokens[i] = token[i];
    }
    program(); // start symbol
    return recognizeGrammar;
}

// program	→ decl_list
void program() {
    decl_list();
}

/* decl_list  → decl_list decl
              | decl
* 토큰의 끝까지 재귀를 고려함.
*/
void decl_list() {
    while (peekToken() != EOF) {
        decl();
    }
}

/* decl	 → var_decl
         | stmt
* 둘 중에 택일해야 하는데 다음 토큰을 가져와서 DATATYPE이면 var_decl으로 분기, 아니면 statement로 분기.
*/
void decl() {
    int nextToken = peekToken();
    if (nextToken == DATATYPE) {
        var_decl();
    } else {
        stmt();
    }
}

/* var_decl		→ type_spec IDENT';'
                | type_spec IDENT'='expr; */
void var_decl() {
    type_spec();
    expectToken(IDENTIFIER);
    if (peekToken() == ASSIGN) {
        getNextToken(); // equal sign 날리기
        expr();
    }
    expectToken(DELIMITER);
}

// stmt	 → expr_stmt
void stmt() {
    expr_stmt();
}


/* 타입 명세(DATATYPE) >> 터미널에 도달함. 최종적으로 해당하지 않으면 error 처리
 * type_spec  → 'char' | 'int' | 'double' | 'short' | 'long' | 'float'
 * */
void type_spec() {
    int nextToken = getNextToken();
    if (nextToken != DATATYPE) {
        error("Expected a type specifier");
    }
}


/* expr_stmt  → IDENT = expr;
 * 터미널 심볼(expr 제외) 각각 예상되는 심볼이 맞는지 확인
 * */
void expr_stmt() {
    expectToken(IDENTIFIER);
    expectToken(ASSIGN);
    expr();
    expectToken(DELIMITER);
}

/* expr			→ expr ('+' | '-' | '*' | '/') expr
                | factor
 * */
void expr() {
    factor();
    while (peekToken() == OPERATOR){
        getNextToken(); // operator 소모
        factor();
    }
}

/* factor     → IDENT
 *            | LIT
 * */
void factor() {
    int nextToken = getNextToken();
    if (nextToken != IDENTIFIER && nextToken != CONST) {
        error("Expected an identifier or literal");
    }
}

int getNextToken() {
    if(tokenIndex >= endOfTokenIndex){
        return EOF;
    }
    int token = tokens[tokenIndex++];
    return tokenClassifier(token);
}

int peekToken() {
    int token = tokens[tokenIndex];
    if(tokenIndex >= endOfTokenIndex){
        return EOF;
    }
    return tokenClassifier(token);
}

void expectToken(int type) {
    int expectType = tokenClassifier(type);
    if (peekToken() != expectType) {
        error("Unexpected token");
    }
    getNextToken();
}

void error(char *msg){
    //printf("error msg : %s\n", msg);
    recognizeGrammar = false;
}


/* 토큰의 번호(상태)로 class 분류 */
int tokenClassifier(int state){
    if(state >= REJECT){
        return UNKNOWN;
    } else if (state >= DATATYPE){
        return DATATYPE;
    } else if (state >= IDENTIFIER){
        return IDENTIFIER;
    } else if (state >= CONST){
        return CONST;
    } else if (state >= OPERATOR){
        return OPERATOR;
    } else if (state >= DELIMITER){
        return DELIMITER;
    } else if (state >= ASSIGN) {
        return ASSIGN;
    } else if (state >= STRING) {
        return CONST;
    } else if (state >= COMMENTS || state == START) {
        return COMMENTS;
    } else {
        return UNKNOWN;
    }
}