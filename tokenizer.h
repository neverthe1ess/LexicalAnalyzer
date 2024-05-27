//
// Created by neverthe1ess on 5/24/24.
//

#ifndef LEXICALANALYZER_TOKENIZER_H
#define LEXICALANALYZER_TOKENIZER_H
#include <stdbool.h>

char *tokenize(char *line);
char *generalTokenizer(char *line);
bool isGeneralSymbol();

#endif //LEXICALANALYZER_TOKENIZER_H
