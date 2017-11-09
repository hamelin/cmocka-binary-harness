#include <cmocka.h>


extern const struct CMUnitTest all_tests[];
extern const int num_tests;


int
main( int argc, char** argv )
{
    _cmocka_run_group_tests( "All tests", all_tests, num_tests, NULL, NULL );
    return 0;
}

