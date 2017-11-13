/*
list* list_setup;
list* list_teardown;
list* list_test_case;


int build_set_setup( void** state )
{
}


int build_set_teardown( void** state )
{
    test_fixture* ar_setup[] = {
        "ABC", "DEF", "GHI", "NOP", NULL };
    char* ar_teardown[] = { "NONE", "DEF", NULL };
    struct
    {
        char* t;
        char* c;
    } ar_test_case[] = {
        { "ABC", "asdf" },
        { "ABC", "qwer" },
        { "DEF", "ghgh" },
        { "DEF", "tyui" },
        { "DEF", "zxcv" },
        { "GHI", "tyty" },
        { "JKL", "vbnm" },
        { "JKL", "uiop" },
        { NULL,  NULL   }
    };
    int i;

    for( i = 0; ar_setup[ i ]; ++i )
    {
        char* fn = NULL;
        asprintf( &fn, "setup_cmocka__%s", ar_setup[ i ] );
        list_push(
                list_setup,
                test_fixture_init( test_fixture_alloc(), ar_setup[ i ], FIXTURE_SETUP, fn )
                );
        free( fn );
    }

    for( i = 0; ar_teardown[ i ]; ++i )
    {
        char* fn = NULL;
        asprintf( &fn, "teardown_cmocka__%s", ar_teardown[ i ] );
        list_push(
                list_teardown,
                test_fixture_init( test_fixture_alloc(), ar_setup[ i ], FIXTURE_TEARDOWN, fn )
                );
        free( fn );
    }

    for( i = 0; ar_test_case[ i ].t; ++i )
    {
        char* fn = NULL;
        asprintf( &fn, "test_cmocka__%s__%s", ar_test_case[ i ].t, ar_test_case[ i ].c );
        list_push(
                list_test_case,
                test_case_init( test_case_alloc(), ar_test_case[ i ].t, ar_test_case[ i ].c, fn )
                );
        free( fn );
    }
}
*/


/*
void build_set_run_test(
        char** az_setup, char** az_teardown, char** az_test_case, 
        */
