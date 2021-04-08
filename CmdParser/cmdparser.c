#include "cmdparser.h"

#define MAX_FULL_PATH_LENGTH 500

#define CMDPARSER_NUM_ESCAPE_CHARACTERS 2
char CMDPARSER_ESCAPE_CHARACTERS[CMDPARSER_NUM_ESCAPE_CHARACTERS] = {'-','/'};

#define CMDPARSER_NUM_PARAMETERS 2
char CMDPARSER_PARAMETERS[CMDPARSER_NUM_PARAMETERS] = {'d','f'};

#define  CMDPARSER_NUM_SWITCHES 0
char CMDPARSER_SWITCHES[CMDPARSER_NUM_SWITCHES] = {};

///Program parameters initializer
PROGRAM_PARAMS* initProgramParams() {
    PROGRAM_PARAMS* newParams = NULL;
    newParams = calloc(1,sizeof(PROGRAM_PARAMS));

    if(newParams == NULL)
    {
        return NULL;
    }

    newParams->filenames = initStringArray();
    if(newParams->filenames == NULL)
    {
        free(newParams);
        return NULL;
    }

    newParams->flags = 0;

    return newParams;
}

///Dispose of program parameters
///@param params program parameters struct to dispose of
void freeProgramParams(PROGRAM_PARAMS* params)
{
    freeStringArray(params->filenames);
    free(params);
}

///Take in command line parameters, return a struct with everything we need.
/// If parameters are formatted badly, return null and set an index in argv at which error occured
///@param argc
///@param argv
///@param params pointer to program params
///@param errorParamIndex pointer to variable where error index is stored, if NULL, no feedback is provided
int parseCmdParams(int argc, char** argv, PROGRAM_PARAMS* params, int* errorParamIndex)
{
    if(params == NULL)
    {
        return EINVAL;
    }

    if(argv == NULL)
    {
        return EINVAL;
    }
    int result = 0;
    for(int i = 1; i < argc; i++)
    {
        if(charIsEscapeCharacter(argv[i][0]))
        {
            if(strlen(argv[i]) == 1)
            {
                *errorParamIndex = i;
                return EINVAL;
            }
            switch (argv[i][1])
            {
                case 'f':
                    if(i == argc - 1)
                    {
                        if(errorParamIndex != NULL)
                        {
                            *errorParamIndex = i;
                        }
                        return EINVAL;
                    }

                    result = parseFilenameString(params,argv[i+1]);
                    i++;
                    if(result != 0)
                    {
                        if(errorParamIndex != NULL)
                        {
                            *errorParamIndex = i;
                        }
                        return EINVAL;
                    }
                    break;

                case 'd':
                    if(i == argc - 1)
                    {
                        if(errorParamIndex != NULL)
                        {
                            *errorParamIndex = i;
                        }
                        return EINVAL;
                    }

                    result = parseDirectoryString(params,argv[i+1]);
                    i++;
                    if(result != 0)
                    {
                        if(errorParamIndex != NULL)
                        {
                            *errorParamIndex = i;
                        }
                        return EINVAL;
                    }
                    break;
            }
        } else {
            return EINVAL;
        }
    }

    return 0;
}

///Checks if character is one of escape characters
///@note Internal function
int charIsEscapeCharacter(char testedChar) {
    for(int i = 0; i < CMDPARSER_NUM_ESCAPE_CHARACTERS; i++)
    {
        if(testedChar == CMDPARSER_ESCAPE_CHARACTERS[i])
        {
            return 1;
        }
    }

    return 0;
}

///Take a string, check it if it is a valid path, and append it to filenames if it is
///@note Internal function
int parseFilenameString(PROGRAM_PARAMS *params, char *filenameString) {
    if(params == NULL)
    {
        return EINVAL;
    }

    if(filenameString == NULL)
    {
        return EINVAL;
    }

    FILE* temp = NULL;
    int result = fopen_s(&temp,filenameString,"rb");
    if(result != 0)
    {
        fclose(temp);
        return result;
    }

    fclose(temp);

    result = appendString(filenameString,&(params->filenames));

    if(result != 0)
    {
        return result;
    }

    return 0;
}

int parseDirectoryString(PROGRAM_PARAMS* params, char* dirString)
{
    if(params == NULL)
    {
        return EINVAL;
    }

    if(dirString == NULL)
    {
        return EINVAL;
    }

    DIR* directory = opendir(dirString);
    if (directory == NULL)
    {
        return ENOENT;
    }
    int result = 0;
    struct dirent* dirEntry = NULL;
    char* fullPath = calloc(MAX_FULL_PATH_LENGTH,sizeof(char));
    while(dirEntry = readdir(directory))
    {
        if((dirEntry->d_namlen == 1 && dirEntry->d_name[0] == '.') ||
                (dirEntry->d_namlen == 2 && dirEntry->d_name[0] == '.' && dirEntry->d_name[1] == '.'))
        {
            continue;
        }
        result = strcpy_s(fullPath,MAX_FULL_PATH_LENGTH,dirString);
        if(result != 0)
        {
            free(fullPath);
            free(dirEntry);
            closedir(directory);
            return ENAMETOOLONG;
        }
        if(fullPath[strlen(fullPath)-1] != '\\')
        {
            result = strcat_s(fullPath,MAX_FULL_PATH_LENGTH,"\\");
            if(result != 0)
            {
                free(fullPath);
                free(dirEntry);
                closedir(directory);
                return ENAMETOOLONG;
            }
        }

        result = strcat_s(fullPath,MAX_FULL_PATH_LENGTH,&(dirEntry->d_name));
        if(result != 0)
        {
            free(fullPath);
            free(dirEntry);
            closedir(directory);
            return ENAMETOOLONG;
        }

        if(isDirectory(fullPath))
        {
            result = parseDirectoryString(params,fullPath);
            if(result != 0)
            {
                free(fullPath);
                free(dirEntry);
                closedir(directory);
                return result;
            }
        } else {

            FILE* temp = NULL;
            result = fopen_s(&temp,fullPath,"rb");
            if(result != 0)
            {
                free(fullPath);
                free(dirEntry);
                closedir(directory);
                fclose(temp);
                return result;
            }

            fclose(temp);

            result = appendString(fullPath,&(params->filenames));

            if(result != 0)
            {
                free(fullPath);
                free(dirEntry);
                closedir(directory);
                return result;
            }

        }
    }

    free(fullPath);
    free(dirEntry);
    closedir(directory);

    return 0;
}

int isDirectory(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}