#include "readelf.h"


test_case* test_case_alloc()
{
    test_case* tc = calloc( 1, sizeof( test_case ) );
    test_case nil = TEST_CASE_NIL;
    memcpy( tc, &nil, sizeof( test_case ) );
    return( tc );
}


void test_case_free( test_case** tc )
{
    if( *tc )
    {
        field_free( &(*tc)->_test );
        field_free( &(*tc)->_case );
        field_free( &(*tc)->_fn );
        free( *tc );
        *tc = NULL;
    }
}


int test_case_parse_symbol( test_case** ptc, const char* symbol )
{
    int r = RESULT_PARSE_SYMBOL_ERROR;
    const char* prefix = "test_cmocka__";
    const char* sep_test_from_case = "__";
    if( !strncmp( symbol, prefix, strlen( prefix ) ) )
    {
        const char* test_and_case = symbol + strlen( prefix );
        const char* sep = strstr( test_and_case, sep_test_from_case );
        if( sep )
        {
            char* testname = strdup( test_and_case );
            testname[ sep - test_and_case ] = '\0';
            const char* casename = sep + strlen( sep_test_from_case );

            if( testname[ 0 ] && casename[ 0 ] )
            {
                *ptc = test_case_alloc();
                test_case_set_fn( *ptc, symbol );
                test_case_set_test( *ptc, testname );
                test_case_set_case( *ptc, sep + strlen( sep_test_from_case ) );
                r = RESULT_PARSE_SYMBOL_SUCCESS;
            }
            else
            {
                r = RESULT_PARSE_SYMBOL_FAILURE;
            }

            free( testname );
        }
        else
        {
            r = RESULT_PARSE_SYMBOL_FAILURE;
        }
    }
    else
    {
        r = RESULT_PARSE_SYMBOL_FAILURE;
    }

    return r;
}


test_fixture* test_fixture_alloc()
{
    test_fixture nil = TEST_FIXTURE_NIL;
    test_fixture* tf = calloc( 1, sizeof( test_fixture ) );
    memcpy( tf, &nil, sizeof( test_fixture ) );
    return tf;
}


void test_fixture_free( test_fixture** ptf )
{
    if( *ptf )
    {
        field_free( &(*ptf)->_test );
        field_free( &(*ptf)->_fn );
        free( *ptf );
        *ptf = NULL;
    }
}


int test_fixture_parse_symbol( test_fixture** ptf, const char* symbol )
{
    const char* marker = "_cmocka__";
    const char* pos_marker = strstr( symbol, marker );
    int r = RESULT_PARSE_SYMBOL_ERROR;
    if( pos_marker )
    {
        fixture_type ftype = FIXTURE_NIL;
        if( !strncmp( symbol, "setup", pos_marker - symbol ) )
        {
            ftype = FIXTURE_SETUP;
        }
        else if( !strncmp( symbol, "teardown", pos_marker - symbol ) )
        {
            ftype = FIXTURE_TEARDOWN;
        }

        if( ftype != FIXTURE_NIL )
        {
            const char* testname = pos_marker + strlen( marker );
            if( testname[ 0 ] )
            {
                *ptf = test_fixture_alloc();
                test_fixture_set_test( *ptf, testname );
                test_fixture_set_type( *ptf, ftype );
                test_fixture_set_fn( *ptf, symbol );
                r = RESULT_PARSE_SYMBOL_SUCCESS;
            }
            else
            {
                r = RESULT_PARSE_SYMBOL_FAILURE;
            }
        }
        else
        {
            r = RESULT_PARSE_SYMBOL_FAILURE;
        }
    }
    else
    {
        r = RESULT_PARSE_SYMBOL_FAILURE;
    }
    return r;
}


int parse_readelf_line( void** ptobj, const char* line_readelf )
{
    int r = RESULT_PARSE_READELF_LINE_ERROR;
    char* line = strdup( line_readelf );  // Copy so as to tokenize.
    char* c = line;
    const char* delim = " \t\n:";

    if( skip_blank( &c ) )
    {
        if( isdigit( *c ) )
        {
            char* save = NULL;
            char* symbol = NULL;
            if( strtok_r( c, delim, &save ) &&                 // Entry number
                    strtok_r( NULL, delim, &save ) &&              // Value
                    strtok_r( NULL, delim, &save ) &&              // Size
                    strtok_r( NULL, delim, &save ) &&              // Type
                    strtok_r( NULL, delim, &save ) &&              // Bind scope
                    strtok_r( NULL, delim, &save ) &&              // Visibility
                    strtok_r( NULL, delim, &save ) &&              // Index
                    ( symbol = strtok_r( NULL, delim, &save ) ) )  // Symbol name, at last!
            {
                if( RESULT_PARSE_SYMBOL_SUCCESS == test_case_parse_symbol( (test_case**)ptobj, symbol ) )
                {
                    r = RESULT_PARSE_READELF_LINE_SUCCESS_TEST_CASE;
                }
                else
                {
                    r = RESULT_PARSE_READELF_LINE_FAILURE;
                }
            }
        }
        else
        {
            r = RESULT_PARSE_READELF_LINE_FAILURE;
        }
    }
    else
    {
        r = RESULT_PARSE_READELF_LINE_ERROR;
    }

    free( line );
    return r;
}
