int utils_setup( void** state );
int utils_teardown( void** state );
void utils_test_set_field_from_null( void** state );
void utils_test_clear_field_from_null( void** state );
void utils_test_set_empty_from_null( void** state );
void utils_test_set_field_from_full( void** state );
void utils_test_clear_field_from_full( void** state );
void utils_test_set_empty_from_full( void** state );
void utils_test_skip_blank_noblank( void** state );
void utils_test_skip_blank_someblank( void** state );
void utils_test_skip_blank_nononblank( void** state );
void utils_test_skip_blank_empty( void** state );

int list_setup( void** state );
int list_teardown( void** state );
void test_list_push_iter( void** state );
void test_list_lookup_present( void** state );
void test_list_lookup_absent( void** state );

int readelf_parse_setup( void** state );
int readelf_parse_teardown( void** state );
void test_test_case_parse_symbol_valid_test( void** state );
void test_test_case_parse_symbol_bad_test_case_sep( void** state );
void test_test_case_parse_symbol_bad_prefix_sep( void** state );
void test_test_case_parse_symbol_other( void** state );
void test_test_case_parse_symbol_no_test_case( void** state );
void test_test_case_parse_symbol_no_test( void** state );
void test_test_case_parse_symbol_no_case( void** state );
void test_parse_readelf_line_with_test( void** state );
void test_parse_readelf_line_with_setup( void** state );
void test_parse_readelf_line_with_teardown( void** state );
void test_parse_readelf_line_func_setup( void** state );
void test_parse_readelf_line_func_teardown( void** state );
void test_parse_readelf_line_func_other( void** state );
void test_parse_readelf_line_symbol_not_func( void** state );
void test_parse_readelf_line_object_file_name( void** state );
void test_parse_readelf_line_empty_line( void** state );
void test_parse_readelf_line_heading( void** state );
void test_parse_readelf_line_symbol_table_summary( void** state );
void test_fixture_parse_symbol_has_setup( void** state );
void test_fixture_parse_symbol_has_teardown( void** state );
void test_fixture_parse_symbol_bad_sep( void** state );
void test_fixture_parse_symbol_other( void** state );
void test_fixture_parse_symbol_no_test( void** state );

const struct CMUnitTest all_tests[] =
{
    cmocka_unit_test_setup_teardown( utils_test_set_field_from_null, utils_setup, utils_teardown),
    cmocka_unit_test_setup_teardown( utils_test_clear_field_from_null, utils_setup, utils_teardown),
    cmocka_unit_test_setup_teardown( utils_test_set_empty_from_null, utils_setup, utils_teardown),
    cmocka_unit_test_setup_teardown( utils_test_set_field_from_full, utils_setup, utils_teardown),
    cmocka_unit_test_setup_teardown( utils_test_clear_field_from_full, utils_setup, utils_teardown),
    cmocka_unit_test_setup_teardown( utils_test_set_empty_from_full, utils_setup, utils_teardown),
    cmocka_unit_test( utils_test_skip_blank_noblank ),
    cmocka_unit_test( utils_test_skip_blank_someblank ),
    cmocka_unit_test( utils_test_skip_blank_nononblank ),
    cmocka_unit_test( utils_test_skip_blank_empty ),
    cmocka_unit_test_setup_teardown( test_list_push_iter, list_setup, list_teardown ),
    cmocka_unit_test_setup_teardown( test_list_lookup_present, list_setup, list_teardown ),
    cmocka_unit_test_setup_teardown( test_list_lookup_absent, list_setup, list_teardown ),
    cmocka_unit_test_setup_teardown( test_test_case_parse_symbol_valid_test, readelf_parse_setup, readelf_parse_teardown ),
    cmocka_unit_test_setup_teardown( test_test_case_parse_symbol_bad_test_case_sep, readelf_parse_setup, readelf_parse_teardown ),
    cmocka_unit_test_setup_teardown( test_test_case_parse_symbol_bad_prefix_sep, readelf_parse_setup, readelf_parse_teardown ),
    cmocka_unit_test_setup_teardown( test_test_case_parse_symbol_other, readelf_parse_setup, readelf_parse_teardown ),
    cmocka_unit_test_setup_teardown( test_test_case_parse_symbol_no_test_case, readelf_parse_setup, readelf_parse_teardown ),
    cmocka_unit_test_setup_teardown( test_test_case_parse_symbol_no_test, readelf_parse_setup, readelf_parse_teardown ),
    cmocka_unit_test_setup_teardown( test_test_case_parse_symbol_no_case, readelf_parse_setup, readelf_parse_teardown ),
    cmocka_unit_test_setup_teardown( test_parse_readelf_line_with_test, readelf_parse_setup, readelf_parse_teardown ),
    cmocka_unit_test_setup_teardown( test_parse_readelf_line_with_setup, readelf_parse_setup, readelf_parse_teardown ),
    cmocka_unit_test_setup_teardown( test_parse_readelf_line_with_teardown, readelf_parse_setup, readelf_parse_teardown ),
    cmocka_unit_test_setup_teardown( test_parse_readelf_line_func_other, readelf_parse_setup, readelf_parse_teardown ),
    cmocka_unit_test_setup_teardown( test_parse_readelf_line_symbol_not_func, readelf_parse_setup, readelf_parse_teardown ),
    cmocka_unit_test_setup_teardown( test_parse_readelf_line_object_file_name, readelf_parse_setup, readelf_parse_teardown ),
    cmocka_unit_test_setup_teardown( test_parse_readelf_line_empty_line, readelf_parse_setup, readelf_parse_teardown ),
    cmocka_unit_test_setup_teardown( test_parse_readelf_line_heading, readelf_parse_setup, readelf_parse_teardown ),
    cmocka_unit_test_setup_teardown( test_parse_readelf_line_symbol_table_summary, readelf_parse_setup, readelf_parse_teardown ),
    cmocka_unit_test_setup_teardown( test_fixture_parse_symbol_has_setup, readelf_parse_setup, readelf_parse_teardown ),
    cmocka_unit_test_setup_teardown( test_fixture_parse_symbol_has_teardown, readelf_parse_setup, readelf_parse_teardown ),
    cmocka_unit_test_setup_teardown( test_fixture_parse_symbol_bad_sep, readelf_parse_setup, readelf_parse_teardown ),
    cmocka_unit_test_setup_teardown( test_fixture_parse_symbol_other, readelf_parse_setup, readelf_parse_teardown ),
    cmocka_unit_test_setup_teardown( test_fixture_parse_symbol_no_test, readelf_parse_setup, readelf_parse_teardown ),
};
const int num_tests = sizeof( all_tests ) / sizeof( all_tests[ 0 ] );
