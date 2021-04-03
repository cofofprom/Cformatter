#ifndef CFORMATTER_MAXLOOPNESTING_H
#define CFORMATTER_MAXLOOPNESTING_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../StringTools/StringTools.h"

char *deleteDoWhile(char *InputString, char *OutputString);

int findLoop(char *InputString, int idx);

void findMaxLoopNesting(char *InputString);

#endif //CFORMATTER_MAXLOOPNESTING_H
