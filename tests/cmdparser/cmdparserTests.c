#include "../../seatest/seatest.h"
#include "../../CmdParser/cmdparser.h"
//
// create a test...
//
void test_file()
{
    const int argc = 3;
    char* param1 = "foo.exe";
    char* param2 = "/f";
    char* param3 = "D:\\Files\\Programming projects\\C lectures\\testdir\\testfile.txt";
    char** argv = calloc(3,sizeof(char*));
    argv[0] = param1;
    argv[1] = param2;
    argv[2] = param3;

    PROGRAM_PARAMS* params = initProgramParams();
    int errorIndex = 0;
    int result = parseCmdParams(argc,argv,params,&errorIndex);
    assert_int_equal(0,result);
    assert_int_equal(0,errorIndex);
    const char* newString = getStringAt(0,params->filenames);
    assert_string_equal(param3,newString);

    freeProgramParams(params);
    free(argv);
}

void test_directory()
{
    const int argc = 3;
    char* param1 = "foo.exe";
    char* param2 = "/d";
    char* param3 = "D:\\Files\\Programming projects\\C lectures\\testdir_mono";
    char** argv = calloc(3,sizeof(char*));
    argv[0] = param1;
    argv[1] = param2;
    argv[2] = param3;

    PROGRAM_PARAMS* params = initProgramParams();
    int errorIndex = 0;
    int result = parseCmdParams(argc,argv,params,&errorIndex);

    assert_int_equal(0,result);
    assert_int_equal(0,errorIndex);

    assert_true(
            !strcmp("D:\\Files\\Programming projects\\C lectures\\testdir_mono\\testfile.txt",getStringAt(0,params->filenames))
            || !strcmp("D:\\Files\\Programming projects\\C lectures\\testdir_mono\\testdir2\\testfile2.txt",getStringAt(0,params->filenames)));
    assert_true(
            !strcmp("D:\\Files\\Programming projects\\C lectures\\testdir_mono\\testfile.txt",getStringAt(1,params->filenames))
            || !strcmp("D:\\Files\\Programming projects\\C lectures\\testdir_mono\\testdir2\\testfile2.txt",getStringAt(1,params->filenames)));
    assert_true(strcmp(getStringAt(0,params->filenames),getStringAt(1,params->filenames)));
    freeProgramParams(params);
    free(argv);
}

test_empty_flags_dir()
{
    const int argc = 2;
    char* param1 = "foo.exe";
    char* param2 = "/d";
    char** argv = calloc(3,sizeof(char*));
    argv[0] = param1;
    argv[1] = param2;

    PROGRAM_PARAMS* params = initProgramParams();
    int errorIndex = 0;
    int result = parseCmdParams(argc,argv,params,&errorIndex);

    assert_int_equal(EINVAL,result);
    assert_int_equal(1,errorIndex);
    assert_int_equal(0,params->filenames->length);
}

test_empty_flags_file()
{
    const int argc = 2;
    char* param1 = "foo.exe";
    char* param2 = "/f";
    char** argv = calloc(3,sizeof(char*));
    argv[0] = param1;
    argv[1] = param2;

    PROGRAM_PARAMS* params = initProgramParams();
    int errorIndex = 0;
    int result = parseCmdParams(argc,argv,params,&errorIndex);

    assert_int_equal(EINVAL,result);
    assert_int_equal(1,errorIndex);
    assert_int_equal(0,params->filenames->length);
}

test_noexist_directory()
{
    const int argc = 3;
    char* param1 = "foo.exe";
    char* param2 = "/d";
    char* param3 = "D:\\Files\\Programming projects\\C lectures\\invalid_dir";
    char** argv = calloc(3,sizeof(char*));
    argv[0] = param1;
    argv[1] = param2;
    argv[2] = param3;

    PROGRAM_PARAMS* params = initProgramParams();
    int errorIndex = 0;
    int result = parseCmdParams(argc,argv,params,&errorIndex);

    assert_int_equal(EINVAL,result);
    assert_int_equal(2,errorIndex);
}

test_noexist_files()
{
    const int argc = 3;
    char* param1 = "foo.exe";
    char* param2 = "/f";
    char* param3 = "D:\\Files\\Programming projects\\C lectures\\invalid_file.txt";
    char** argv = calloc(3,sizeof(char*));
    argv[0] = param1;
    argv[1] = param2;
    argv[2] = param3;

    PROGRAM_PARAMS* params = initProgramParams();
    int errorIndex = 0;
    int result = parseCmdParams(argc,argv,params,&errorIndex);

    assert_int_equal(EINVAL,result);
    assert_int_equal(2,errorIndex);
}

test_file_as_dir()
{
    const int argc = 3;
    char* param1 = "foo.exe";
    char* param2 = "/d";
    char* param3 = "D:\\Files\\Programming projects\\C lectures\\testfile.txt";
    char** argv = calloc(3,sizeof(char*));
    argv[0] = param1;
    argv[1] = param2;
    argv[2] = param3;

    PROGRAM_PARAMS* params = initProgramParams();
    int errorIndex = 0;
    int result = parseCmdParams(argc,argv,params,&errorIndex);

    assert_int_equal(EINVAL,result);
    assert_int_equal(2,errorIndex);
}

test_dir_as_file()
{
    const int argc = 3;
    char* param1 = "foo.exe";
    char* param2 = "/f";
    char* param3 = "D:\\Files\\Programming projects\\C lectures\\testdir";
    char** argv = calloc(3,sizeof(char*));
    argv[0] = param1;
    argv[1] = param2;
    argv[2] = param3;

    PROGRAM_PARAMS* params = initProgramParams();
    int errorIndex = 0;
    int result = parseCmdParams(argc,argv,params,&errorIndex);

    assert_int_equal(EINVAL,result);
    assert_int_equal(2,errorIndex);
}

test_multidir()
{
    const int argc = 5;
    char* param1 = "foo.exe";
    char* param2 = "/d";
    char* param3 = "D:\\Files\\Programming projects\\C lectures\\testdir\\testdir2";
    char* param4 = "/d";
    char* param5 = "D:\\Files\\Programming projects\\C lectures\\testdir\\testdir3";
    char** argv = calloc(3,sizeof(char*));
    argv[0] = param1;
    argv[1] = param2;
    argv[2] = param3;
    argv[3] = param4;
    argv[4] = param5;

    PROGRAM_PARAMS* params = initProgramParams();
    int errorIndex = 0;
    int result = parseCmdParams(argc,argv,params,&errorIndex);

    assert_int_equal(0,result);
    assert_int_equal(0,errorIndex);
    assert_int_equal(3,params->filenames->length);

    freeProgramParams(params);
    free(argv);
}

test_multifile()
{
    const int argc = 5;
    char* param1 = "foo.exe";
    char* param2 = "/f";
    char* param3 = "D:\\Files\\Programming projects\\C lectures\\testdir\\testfile.txt";
    char* param4 = "/f";
    char* param5 = "D:\\Files\\Programming projects\\C lectures\\testdir\\testdir3\\testfile3.txt";
    char** argv = calloc(3,sizeof(char*));
    argv[0] = param1;
    argv[1] = param2;
    argv[2] = param3;
    argv[3] = param4;
    argv[4] = param5;

    PROGRAM_PARAMS* params = initProgramParams();
    int errorIndex = 0;
    int result = parseCmdParams(argc,argv,params,&errorIndex);

    assert_int_equal(0,result);
    assert_int_equal(0,errorIndex);
    assert_int_equal(2,params->filenames->length);

    freeProgramParams(params);
    free(argv);
}

//
// put the test into a fixture...
//
void test_fixture_cmdparser( void )
{
    test_fixture_start();
    run_test(test_file);
    run_test(test_directory);
    run_test(test_empty_flags_dir);
    run_test(test_empty_flags_file);
    run_test(test_noexist_directory);
    run_test(test_noexist_files);
    run_test(test_file_as_dir);
    run_test(test_dir_as_file);
    run_test(test_multidir);
    run_test(test_multifile);
    test_fixture_end();
}

//
// put the fixture into a suite...
//
void all_tests( void )
{
    test_fixture_cmdparser();
}

//
// run the suite!
//
int main( int argc, char** argv )
{
    return run_tests(all_tests);
}