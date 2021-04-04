#include "../../seatest.h"
#include "../../stringarray.h"
//
// create a test...
//
void test_dummy()
{
    int reference = 2;
    assert_int_equal(reference,dummy(reference));
}

//
// put the test into a fixture...
//
void test_fixture_dummy( void )
{
    test_fixture_start();
    run_test(test_dummy);
    test_fixture_end();
}

//
// put the fixture into a suite...
//
void all_tests( void )
{
    test_fixture_dummy();
}

//
// run the suite!
//
int main( int argc, char** argv )
{
    return run_tests(all_tests);
}