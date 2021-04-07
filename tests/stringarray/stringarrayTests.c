#include "../../seatest/seatest.h"
#include "../../StringArray/stringarray.h"
//
// create a test...
//
void test_main()
{
    char* testString1 = "String1";
    char* testString2 = "String2";
    char* testString3 = "String3";
    STRING_ARRAY* referenceStringArray = initStringArray();
    assert_false(referenceStringArray == NULL);
    assert_true(referenceStringArray->length == 0);
    assert_true(referenceStringArray->allocatedLength == 50);
    int appendResult = appendString(testString1,&referenceStringArray);
    assert_int_equal(0,appendResult);
    assert_string_equal(testString1,referenceStringArray->strings[0]);
    assert_string_equal(NULL,referenceStringArray->strings[1]);
    appendResult = appendString(testString2,&referenceStringArray);
    assert_int_equal(0,appendResult);
    assert_string_equal(testString2,referenceStringArray->strings[1]);
    assert_string_equal(NULL,referenceStringArray->strings[2]);
    appendResult = appendString(NULL,&referenceStringArray);
    assert_int_equal(EINVAL,appendResult);
    appendResult = appendString(testString3,NULL);
    assert_int_equal(EINVAL,appendResult);
    int deleteResult = deleteStringAt(10,referenceStringArray);
    assert_int_equal(EINVAL,deleteResult);
    appendString(testString3,&referenceStringArray);
    char* temp = referenceStringArray->strings[1];
    referenceStringArray->strings[1] = NULL;
    deleteResult = deleteStringAt(1,referenceStringArray);
    assert_int_equal(EFAULT,deleteResult);
    referenceStringArray->strings[1] = temp;
    deleteResult = deleteStringAt(1,referenceStringArray);
    assert_int_equal(0,deleteResult);
    assert_string_equal(testString3,referenceStringArray->strings[1]);
    assert_string_equal(testString3,getStringAt(1,referenceStringArray));
    assert_string_equal(NULL,getStringAt(2,referenceStringArray));
}

//
// put the test into a fixture...
//
void test_fixture_main( void )
{
    test_fixture_start();
    run_test(test_main);
    test_fixture_end();
}

//
// put the fixture into a suite...
//
void all_tests( void )
{
    test_fixture_main();
}

//
// run the suite!
//
int main( int argc, char** argv )
{
    return run_tests(all_tests);
}