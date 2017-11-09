#include "readelf.h"


test_case* test_case_alloc()
{
    test_case* tc = calloc( 1, sizeof( test_case ) );
    memset( tc, 0, sizeof( test_case ) );
    return( tc );
}


void test_case_free( test_case** tc )
{
    field_free( &(*tc)->_test );
    field_free( &(*tc)->_case );
    field_free( &(*tc)->_fn );
    free( *tc );
    *tc = NULL;
}


int test_case_parse_symbol( test_case* tc, const char* symbol )
{
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

            test_case_set_fn( tc, symbol );
            test_case_set_test( tc, testname );
            test_case_set_case( tc, sep + strlen( sep_test_from_case ) );

            free( testname );
            return RESULT_PARSE_SYMBOL_SUCCESS;
        }
        else
        {
            return RESULT_PARSE_SYMBOL_FAILURE;
        }
    }
    else
    {
        return RESULT_PARSE_SYMBOL_FAILURE;
    }
}


int parse_readelf_line( test_case* tc, const char* line_readelf )
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
                if( RESULT_PARSE_SYMBOL_SUCCESS == test_case_parse_symbol( tc, symbol ) )
                {
                    r = RESULT_PARSE_READELF_LINE_SUCCESS;
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
