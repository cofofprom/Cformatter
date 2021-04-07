#include <stdio.h>
#include "Formatter/Formatter.h"
#include <stdlib.h>
int main() {
    char* content = readCode("test.c");
    char* res = deleteFormat(content);
    printf("%s", res);
    return 0;
}
