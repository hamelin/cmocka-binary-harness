void* ptr_freed_last = NULL;


void __wrap_free( void* p )
{
    void __real_free( void* );
    ptr_freed_last = p;
    __real_free( p );
}
