#ifndef READELF_H__
#define READELF_H__


typedef struct _test_case
{
    char* _test;
    char* _case;
    char* _fn;
} test_case;

#define TEST_CASE( name_test, name_case, name_fn )   { (name_test), (name_case), (name_fn) }
#define TEST_CASE_NIL                                TEST_CASE( NULL, NULL, NULL )
test_case* test_case_make();
void test_case_free( test_case** tc );
#define test_case_get_test( tc )      (tc)->_test
#define test_case_get_case( tc )      (tc)->_case
#define test_case_get_fn( tc )        (tc)->_fn
#define test_case_set_test( tc, t )   field_set_string( &(tc)->_test, (t) )
#define test_case_set_case( tc, c )   field_set_string( &(tc)->_case, (c) )
#define test_case_set_fn( tc, fn )    field_set_string( &(tc)->_fn, (fn) )

#define RESULT_PARSE_SYMBOL_SUCCESS    0
#define RESULT_PARSE_SYMBOL_FAILURE    1
#define RESULT_PARSE_SYMBOL_ERROR     -1
int test_case_parse_symbol( test_case* tc, const char* symbol );


#define RESULT_PARSE_READELF_LINE_SUCCESS    0
#define RESULT_PARSE_READELF_LINE_FAILURE    1
#define RESULT_PARSE_READELF_LINE_ERROR     -1
int parse_readelf_line( test_case* tc, const char* line_readelf );


#endif  // READELF_H__
