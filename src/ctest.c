extern setup_fn do_setup;
extern teardown_fn do_teardown;
extern ctest* all;


bool cmp_write_str0( cmp_ctx_t* ctx, const char* sz )
{
    return( cmp_write_str( ctx, sz, strlen( sz ) ) );
}


void list_tests( cmp_ctx_t* ctx )
{
    abort();
}


ctest_fn find_test( const char* name )
{
    abort();
    return NULL;
}


void report_failure( cmp_ctx_t* ctx )
{
    abort();
}


int main( int argc, char** argv )
{
    int r = 0;
    cmp_ctx_t ctx;

    cmp_init_stdio( &ctx, stdout );
    if( argc < 2 )
    {
        list_tests( &ctx );
    }
    else
    {
        ctest_fn test;

        if( NULL != ( test = find_test( argv[ 1 ] ) ) )
        {
            if( NULL != do_setup )
            {
                do_setup();
            }
            test();
            if( NULL != do_teardown )
            {
                do_teardown();
            }
            report_failure( &ctx );
        }
        else
        {
            fprintf( stderr, "Unknown parameter: %s\n", argv[ 1 ] );
            r = 1;
        }
    }

    return r;
}
