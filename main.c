#include <stdio.h>
#include "Formatter/Formatter.h"
#include <stdlib.h>
int main() {
    char* content = readCode("test.c");
    char* res = formatCode(content);
    FILE* f = fopen("out.txt", "wb");
    fprintf(f,"%s", res);
    fclose(f);
    return 0;
}
