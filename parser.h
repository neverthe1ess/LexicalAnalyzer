#ifndef LEXICALANALYZER_PARSER_H
#define LEXICALANALYZER_PARSER_H
#include "fsmbyToken.h"
#include "stdbool.h"

bool parser(int tokenStates[], int tokenCount);
void program();
void decl_list();
void decl();
void var_decl();
void type_spec();
void stmt();
void expr_stmt();
void expr();
void factor();
void error(char *msg);
void expectToken(int type);
int getNextToken();
int peekToken();
int tokenClassifier(int state);

#endif //LEXICALANALYZER_PARSER_H
