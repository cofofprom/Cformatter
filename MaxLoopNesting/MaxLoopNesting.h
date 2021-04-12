#ifndef CFORMATTER_MAXLOOPNESTING_H
#define CFORMATTER_MAXLOOPNESTING_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../StringTools/StringTools.h"

char *deleteDoWhile(char *InputString, char *OutputString);

int findLoop(char *InputString, int idx);

char *makeAllLoopsMultiline(char *InputString);

void findMaxLoopNesting(char *InputString, int *Shift, int *CountBrackets);

void printMaxLoopNesting(char *InputString);

#endif //CFORMATTER_MAXLOOPNESTING_H
