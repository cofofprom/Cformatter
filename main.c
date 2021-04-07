#include <stdio.h>
#include "Formatter/Formatter.h"
int main() {
    char* content = readCode("test.c");
    printf("%s", formatCode(content));
    return 0;
}
