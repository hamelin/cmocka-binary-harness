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
test_case* test_case_alloc();
void test_case_free( test_case** tc );
#define test_case_get_test( tc )      (tc)->_test
#define test_case_get_case( tc )      (tc)->_case
#define test_case_get_fn( tc )        (tc)->_fn
#define test_case_set_test( tc, t )   field_set_string( &(tc)->_test, (t) )
#define test_case_set_case( tc, c )   field_set_string( &(tc)->_case, (c) )
#define test_case_set_fn( tc, fn )    field_set_string( &(tc)->_fn, (fn) )

typedef struct _test_fixture
{
    char* _test;
    int _fixture;
    char* _fn;
} test_fixture;

#define FIXTURE_NIL       0
#define FIXTURE_SETUP     1
#define FIXTURE_TEARDOWN  2

#define TEST_FIXTURE(test, fixture, fn)    { (test), (fixture), (fn) }
#define TEST_FIXTURE_NIL                   { NULL, FIXTURE_NIL, NULL }

#define RESULT_PARSE_SYMBOL_SUCCESS    0
#define RESULT_PARSE_SYMBOL_FAILURE    1
#define RESULT_PARSE_SYMBOL_ERROR     -1
int test_case_parse_symbol( test_case** ptc, const char* symbol );
int test_fixture_parse_symbol( test_fixture** ptf, const char* symbol );


#define RESULT_PARSE_READELF_LINE_FAILURE             0
#define RESULT_PARSE_READELF_LINE_SUCCESS_TEST_CASE   1
#define RESULT_PARSE_READELF_LINE_SUCCESS_SETUP       2
#define RESULT_PARSE_READELF_LINE_SUCCESS_TEARDOWN    3
#define RESULT_PARSE_READELF_LINE_ERROR              -1
int parse_readelf_line( void** ptobj, const char* line_readelf );


#endif  // READELF_H__
