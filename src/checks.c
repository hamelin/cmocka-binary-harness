#include "ctest.h"


failure the_failure = { 0 };


void _fail( const char* file, int line )
{
    the_failure.file = file;
    the_failure.line = line;
}

void failure_reset()
{
    _fail( NULL, 0 );
}


// EOF
