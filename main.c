#include <stdio.h>
#include "Formatter/Formatter.h"
#include <stdlib.h>
#include "StringArray/stringarray.h"
#include "CmdParser/cmdparser.h"
#include "MaxLoopNesting/MaxLoopNesting.h"
#include "CamelAndPascalCases/CamelCase.h"
#include "CamelAndPascalCases/PascalCase.h"
#include "CheckVariablesAndFunctions/CheckVariables.h"
#include "CheckVariablesAndFunctions/RemovePreprocessors.h"
#include "ChangeCommets/ChangeComments.h"

#define SIZE_OF_FILE 1024

int main(int argc, char *argv[])
{
    PROGRAM_PARAMS *params = initProgramParams();
    int errorParamIndex = 0;
    parseCmdParams(argc, argv, params, &errorParamIndex);
    for (int i = 0; i < params->filenames->length; i++)
    {
        char *filename = params->filenames->strings[i];
        char outfname[SIZE_OF_FILE] = {'o', 'u', 't', '\\', 0};
        int outpos = 4;
        for (int j = 0; j < strlen(filename); j++)
        {
            if (filename[j] == '\\')
            {
                outpos = 4;
                continue;
            }

            outfname[outpos++] = filename[j];
        }
        outfname[outpos] = 0;
        strcat(outfname, "_out.c");
        FILE *out = fopen(outfname, "w");
        printf("Analyzing %s...\n", filename);
        char *code = readCode(filename);
        code = formatCode(code);
        code = replaceWithCamelCase(code);
        code = replaceWithPascalCase(code);
        code = changeComment(code);
        fprintf(out, "%s\n", code);
        fclose(out);
        printf("Formatted code printed out to %s\n\n", outfname);
        if (filename[strlen(filename) - 1] != 'h')
        {
            printMaxLoopNesting(code);
            checkFunctionsForRecursion(code);
            printVariables(code);
            checkName(code);
            printUnusedFunctions(code);
            printUnusedVariables(code);
            printf("\n");
            DEBUG_FUNC(code);
            printf("\n");
            DEBUG_VARS(code);
            printf("\n\n");
        }
    }
    return 0;
}