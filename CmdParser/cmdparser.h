#ifndef C_FORMATTER_CMDPARSER_H
#define C_FORMATTER_CMDPARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include <stdint.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../StringArray/stringarray.h"


///
/// PROGRAM PARAMETERS:
/// d - input directory
/// f - input file
///

struct program_params_struct
{
    STRING_ARRAY* filenames;
    int64_t flags;
};

typedef struct program_params_struct PROGRAM_PARAMS;

PROGRAM_PARAMS* initProgramParams();
void freeProgramParams(PROGRAM_PARAMS* params);

int parseCmdParams(int argc, char** argv, PROGRAM_PARAMS* params, int* errorParamIndex);

int charIsEscapeCharacter(char testedChar);

int parseFilenameString(PROGRAM_PARAMS* params,char* filenameString);

int parseDirectoryString(PROGRAM_PARAMS* params,char* dirString);

int isDirectory(const char *path);

#endif //C_FORMATTER_CMDPARSER_H
