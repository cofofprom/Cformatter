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

int main(int argc, char *argv[])
{
    PROGRAM_PARAMS *params = initProgramParams();
    int errorParamIndex = 0;
    parseCmdParams(argc, argv, params, &errorParamIndex);
    for (int i = 0; i < params->filenames->length; i++)
    {
        char *filename = params->filenames->strings[i];
        if (filename[strlen(filename) - 1] != 'h')
        {
            char outfname[1024] = {'o', 'u', 't', '\\', 0};
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
            printf("Formatted code printed out to %s\n", outfname);
            fprintf(out, "%s", code);
            printMaxLoopNesting(code);
            checkFunctionsForRecursion(code);
            printVariables(code);
            checkName(code);
            printUnusedFunctions(code);
            printf("\n");
            fclose(out);
        }
    }
    return 0;
}