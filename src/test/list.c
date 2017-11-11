typedef struct
{
    char* str;
    int num;
} stuff;


stuff list_stuff_content[] =
{
    { "asdf", 78 },
    { "hoho", -903 },
    { "zxcv", 0 },
    { "qwer", 34 },
    { "uiop", 1 },
    { NULL, 0 }
};


stuff* stuff_alloc()
{
    return calloc( 1, sizeof( stuff ) );
}


stuff* stuff_init( stuff* s, const char* str, int num )
{
    s->str = strdup( str );
    s->num = num;
    return s;
}


void free_stuff( stuff** ps )
{
    if( *ps )
    {
        free( (*ps)->str );
        free( *ps );
        *ps = NULL;
    }
}


bool stuff_match_str( void* vs, const void* vstr )
{
    return !strcmp( ((const stuff*)vs)->str, (const char*)vstr );
}


bool stuff_match_num( void* vs, const void* vnum )
{
    return ((const stuff*)vs)->num == (long long)vnum;
}


list* list_stuff = NULL;


int list_setup( void** state )
{
    int i;

    list_stuff = list_alloc();
    for( i = 0; list_stuff_content[ i ].str; ++i )
    {
        stuff* s = stuff_alloc();
        memcpy( s, list_stuff_content + i, sizeof( stuff ) );
        list_push( list_stuff, s );
    }
    return 0;
}


int list_teardown( void** state )
{
    if( list_stuff )
    {
        list_free( &list_stuff );
    }
    return 0;
}



void test_list_push_iter( void** state )
{
    int i;
    list_iter* iter;
    const char* expected_content[] =
    {
        "asdf",
        "qwerty",
        "zxcv",
        NULL
    };
    list* ll = NULL;

    ll = list_init( list_alloc(), free_malloc );
    list_push( ll, strdup( expected_content[ 2 ] ) );
    list_push( ll, strdup( expected_content[ 1 ] ) );
    list_push( ll, strdup( expected_content[ 0 ] ) );

    for(
            i = 0, iter = list_make_iter( ll );
            expected_content[ i ] && !list_iter_is_at_end( iter );
            ++i, list_iter_next( iter )  )
    {
        assert_string_equal( expected_content[ i ], list_iter_get( iter ) );
    }
    assert_int_equal( LEN_STATIC_ZARRAY( expected_content ), i );
    list_iter_free( iter );
}


void assert_stuff_equal( const char* str, int num, const stuff* s )
{
    assert_string_equal( str, s->str );
    assert_int_equal( num, s->num );
}


void test_list_lookup_present( void** state )
{
    const stuff* s;
    s = list_lookup( list_stuff, stuff_match_str, "qwer" );
    assert_stuff_equal( "qwer", 34, s );
    s = list_lookup( list_stuff, stuff_match_str, "asdf" );
    assert_stuff_equal( "asdf", 78, s );
    s = list_lookup( list_stuff, stuff_match_num, as_obj( -903 ) );
    assert_stuff_equal( "hoho", -903, s );
}


void test_list_lookup_absent( void** state )
{
    assert_null( list_lookup( list_stuff, stuff_match_str, "not there" ) );
    assert_null( list_lookup( list_stuff, stuff_match_num, as_obj( 73 ) ) );
}
