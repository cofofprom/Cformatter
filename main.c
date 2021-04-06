#include <stdio.h>
#include "MaxLoopNesting/MaxLoopNesting.h"
int main() {
    char input[1024] = "do { i++; } while(x > 0)";
    char output[1024] = { 0 };
    deleteDoWhile(input, output);
    printf("%s", output);
    return 0;
}
