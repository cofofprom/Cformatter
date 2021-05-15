#ifndef CFORMATTER_REMOVEPREPROCESSORS_H
#define CFORMATTER_REMOVEPREPROCESSORS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../StringTools/StringTools.h"

#define SIZE 100
#define bool int
#define true 1
#define false 0
#define SIZE_OF_CODE 1024*10

char *changeMacro(char *Code);

char *changeTypedef(char *Code);

#endif //CFORMATTER_REMOVEPREPROCESSORS_H
