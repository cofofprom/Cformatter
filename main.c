#include <stdio.h>
#include "Formatter/Formatter.h"
#include <stdlib.h>
#include "StringArray/stringarray.h"
#include "CmdParser/cmdparser.h"
#include "MaxLoopNesting/MaxLoopNesting.h"
#include "CamelCase/CamelCase.h"
int main(int argc, char* argv[]) {
    FILE* out = fopen("out.txt", "w");
    PROGRAM_PARAMS* params = initProgramParams();
    int errorParamIndex = 0;
    parseCmdParams(argc, argv, params, &errorParamIndex);
    char* inFilename = params->filenames->strings[0];
    char* code = readCode(inFilename);
    code = formatCode(code);
    //code = replaceWithCamelCase(code);
    printf("Formatted code printed out to out.txt\n");
    fprintf(out,"%s", code);
    printMaxLoopNesting(code);
}
