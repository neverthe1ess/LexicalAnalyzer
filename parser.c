//
// Created by neverthe1ess on 6/1/24.
//

#include <stdio.h>
#include "parser.h"

void parser(int tokenStates[], int tokenCount){
    for (int i = 0; i < tokenCount; i++) {
        printf("%d ", tokenStates[i]);
    }
}