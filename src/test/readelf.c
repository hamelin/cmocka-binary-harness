#include <signal.h>
#include "readelf.h"


static test_case* tc = NULL;
static test_fixture* tf = NULL;


int readelf_setup( void** state )
{
    tc = NULL;
    tf = NULL;
    return 0;
}


int readelf_teardown( void** state )
{
    test_case_free( &tc );
    test_fixture_free( &tf );
    return 0;
}


void assert_test_case_equal(
        const char* expected_test,
        const char* expected_case,
        const char* expected_fn,
        const test_case* tc
        )
{
    assert_string_equal( expected_test, test_case_get_test( tc ) );
    assert_string_equal( expected_case, test_case_get_case( tc ) );
    assert_string_equal( expected_fn, test_case_get_fn( tc ) );
}


void test_test_case_parse_symbol_valid_test( void** state )
{
    assert_int_equal(
            RESULT_PARSE_SYMBOL_SUCCESS,
            test_case_parse_symbol( &tc, "test_cmocka__NAME_TEST__dummy_case" )
            );
    assert_test_case_equal( "NAME_TEST", "dummy_case", "test_cmocka__NAME_TEST__dummy_case", tc );
}


void test_test_case_parse_symbol_bad_test_case_sep( void** state )
{
    assert_int_equal(
            RESULT_PARSE_SYMBOL_FAILURE,
            test_case_parse_symbol( &tc, "test_cmocka__asdf_qwerty" )
            );
    assert_null( tc );
}


void test_test_case_parse_symbol_bad_prefix_sep( void** state )
{
    assert_int_equal(
            RESULT_PARSE_SYMBOL_FAILURE,
            test_case_parse_symbol( &tc, "test_cmocka_asdf__qwerty" )
            );
    assert_null( tc );
}


void test_test_case_parse_symbol_other( void** state )
{
    assert_int_equal(
            RESULT_PARSE_SYMBOL_FAILURE,
            test_case_parse_symbol( &tc, "__whatever" )
            );
    assert_null( tc );
}


void test_test_case_parse_symbol_no_test_case( void** state )
{
    assert_int_equal(
            RESULT_PARSE_SYMBOL_FAILURE,
            test_case_parse_symbol( &tc, "test_cmocka__" )
            );
    assert_null( tc );
}


void test_test_case_parse_symbol_no_test( void** state )
{
    assert_int_equal(
            RESULT_PARSE_SYMBOL_FAILURE,
            test_case_parse_symbol( &tc, "test_cmocka____case" )
            );
    assert_null( tc );
}


void test_test_case_parse_symbol_no_case( void** state )
{
    assert_int_equal(
            RESULT_PARSE_SYMBOL_FAILURE,
            test_case_parse_symbol( &tc, "test_cmocka__TEST__" )
            );
    assert_null( tc );
}


void test_parse_readelf_line_with_test( void** state )
{
    assert_int_equal(
            RESULT_PARSE_READELF_LINE_SUCCESS_TEST_CASE,
            parse_readelf_line(
                (void**)&tc,
                "    3: 0000000000000000    17 FUNC    GLOBAL DEFAULT    1 test_cmocka__NAME__dummy\n"
                )
            );
    assert_test_case_equal( "NAME", "dummy", "test_cmocka__NAME__dummy", tc );
}


void check_parse_failure( const char* readelf_line )
{
    assert_int_equal(
            RESULT_PARSE_READELF_LINE_FAILURE,
            parse_readelf_line( (void**)&tc, readelf_line )
            );
    assert_null( tc );
}


void test_parse_readelf_line_func_setup( void** state )
{
    check_parse_failure(
            "    17: 0000000000000000    25 FUNC    GLOBAL DEFAULT    1 setup_cmocka__NAME\n"
            );
}


void test_parse_readelf_line_func_teardown( void** state )
{
    check_parse_failure(
            "    20: 0000000000000000    23 FUNC    GLOBAL DEFAULT    1 teardown_cmocka__NAME\n"
            );
}


void test_parse_readelf_line_func_other( void** state )
{
    check_parse_failure(
            "     9: 0000000000000000   234 FUNC    GLOBAL DEFAULT    1 some_routine\n"
            );
}


void test_parse_readelf_line_symbol_not_func( void** state )
{
    check_parse_failure(
            "    12: 000000000000001c     0 NOTYPE  LOCAL  DEFAULT    5 .LC3\n"
            );
    check_parse_failure(
            "    27: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND _GLOBAL_OFFSET_TABLE_\n"
            );
    check_parse_failure(
            "    12: 0000000000000000   600 OBJECT  GLOBAL DEFAULT    7 all_tests\n"
            );
}


void test_parse_readelf_line_object_file_name( void** state )
{
    check_parse_failure(
            "File: build/release/libtest.a(readelf.o)\n"
            );
}


void test_parse_readelf_line_empty_line( void** state )
{
    check_parse_failure( "\n" );
}


void test_parse_readelf_line_heading( void** state )
{
    check_parse_failure(
            "   Num:    Value          Size Type    Bind   Vis      Ndx Name\n"
            );
}


void test_parse_readelf_line_symbol_table_summary( void** state )
{
    check_parse_failure(
            "Symbol table '.symtab' contains 47 entries:\n"
            );
}


void check_test_fixture( const char* t, fixture_type ft, const char* f )
{
    assert_string_equal( t, test_fixture_get_test( tf ) );
    assert_int_equal( ft, test_fixture_get_type( tf ) );
    assert_string_equal( f, test_fixture_get_fn( tf ) );
}


void test_fixture_parse_symbol_has_setup( void** state )
{
    assert_int_equal(
            RESULT_PARSE_SYMBOL_SUCCESS,
            test_fixture_parse_symbol( &tf, "setup_cmocka__TEST_NAME" )
            );
    check_test_fixture( "TEST_NAME", FIXTURE_SETUP, "setup_cmocka__TEST_NAME" );
}


void test_fixture_parse_symbol_has_teardown( void** state )
{
    assert_int_equal(
            RESULT_PARSE_SYMBOL_SUCCESS,
            test_fixture_parse_symbol( &tf, "teardown_cmocka___thisTestInstead" )
            );
    check_test_fixture( "_thisTestInstead", FIXTURE_TEARDOWN, "teardown_cmocka___thisTestInstead" );
}


void test_fixture_parse_symbol_bad_sep( void** state )
{
    assert_int_equal(
            RESULT_PARSE_SYMBOL_FAILURE,
            test_fixture_parse_symbol( &tf, "setup_cmocka_TEST" )
            );
    assert_null( tf );
    assert_int_equal(
            RESULT_PARSE_SYMBOL_FAILURE,
            test_fixture_parse_symbol( &tf, "teardown_cmockaTEST" )
            );
    assert_null( tf );
}


void test_fixture_parse_symbol_other( void** state )
{
    assert_int_equal(
            RESULT_PARSE_SYMBOL_FAILURE,
            test_fixture_parse_symbol( &tf, "__whatever" )
            );
    assert_null( tf );
}


void test_fixture_parse_symbol_no_test( void** state )
{
    assert_int_equal(
            RESULT_PARSE_SYMBOL_FAILURE,
            test_fixture_parse_symbol( &tf, "setup_cmocka__" )
            );
    assert_null( tf );
    assert_int_equal(
            RESULT_PARSE_SYMBOL_FAILURE,
            test_fixture_parse_symbol( &tf, "teardown_cmocka__" )
            );
    assert_null( tf );
}
