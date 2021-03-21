#ifndef C_FORMATTER_CMDPARSER_H
#define C_FORMATTER_CMDPARSER_H

#include "stringarray.h"

typedef struct program_params_struct PROGRAM_PARAMS;

PROGRAM_PARAMS* initProgramParams();
void freeProgramParams(PROGRAM_PARAMS* params);

//Take in command line parameters, return a struct with everything we need
PROGRAM_PARAMS* parseCmdParams(int argc, char** argv);

#endif //C_FORMATTER_CMDPARSER_H
