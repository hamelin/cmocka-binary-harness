#include "utils.h"


static char* field = NULL;


int utils_setup( void** state )
{
    field = NULL;
    return 0;
}


int utils_teardown( void** state )
{
    if( field )
    {
        free( field );
        field = NULL;
    }
    return 0;
}


void utils_test_set_field_from_null( void** state )
{
    field_set_string( &field, "HOHO" );
    assert_string_equal( "HOHO", field );
}


void utils_test_clear_field_from_null( void** state )
{
    field_set_string( &field, NULL );
    assert_null( field );
}


void utils_test_set_empty_from_null( void** state )
{
    field_set_string( &field, "" );
    assert_null( field );
}


void utils_test_set_field_from_full( void** state )
{
    char* orig = field = strdup( "asdf" );
    field_set_string( &field, "qwerty" );
    assert_ptr_equal( ptr_freed_last, orig );
    assert_string_equal( "qwerty", field );
}


void utils_test_clear_field_from_full( void** state )
{
    char* orig = field = strdup( "asdf" );
    field_set_string( &field, NULL );
    assert_ptr_equal( ptr_freed_last, orig );
    assert_null( field );
}


void utils_test_set_empty_from_full( void** state )
{
    char* orig = field = strdup( "asdf" );
    field_set_string( &field, "" );
    assert_ptr_equal( ptr_freed_last, orig );
    assert_null( field );
}


void utils_test_skip_blank_noblank( void** state )
{
    char s[ 16 ] = "a";
    char* p = s;
    assert_ptr_equal( s, skip_blank( &p ) );
    assert_int_equal( 'a', *p );
}


void utils_test_skip_blank_someblank( void** state )
{
    char s[ 16 ] = " \t a";
    char* p = s;
    assert_ptr_equal( s + 3, skip_blank( &p ) );
    assert_int_equal( 'a', *p );
}


void utils_test_skip_blank_nononblank( void** state )
{
    char s[ 16 ] = "   \t";
    char* p = s;
    assert_ptr_equal( s + 4, skip_blank( &p ) );
    assert_int_equal( 0, *p );
}


void utils_test_skip_blank_empty( void** state )
{
    char s[ 16 ] = "";
    char* p = s;
    assert_ptr_equal( s, skip_blank( &p ) );
    assert_int_equal( 0, *p );
}
