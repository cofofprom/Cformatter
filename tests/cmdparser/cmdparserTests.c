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
    char* param3 = "D:\\Files\\Programming projects\\C lectures\\testdir";
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
            !strcmp("D:\\Files\\Programming projects\\C lectures\\testdir\\testfile.txt",getStringAt(0,params->filenames))
            || !strcmp("D:\\Files\\Programming projects\\C lectures\\testdir\\testdir2\\testfile2.txt",getStringAt(0,params->filenames)));
    assert_true(
            !strcmp("D:\\Files\\Programming projects\\C lectures\\testdir\\testfile.txt",getStringAt(1,params->filenames))
            || !strcmp("D:\\Files\\Programming projects\\C lectures\\testdir\\testdir2\\testfile2.txt",getStringAt(1,params->filenames)));
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
    //TODO write this test
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