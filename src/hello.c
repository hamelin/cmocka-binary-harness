#include <stdlib.h>


const char* str_array[] = { "Hello world!", "HOHO", NULL };

const char*
hello()
{
    return str_array[ 0 ];
}


int
main( int argc, char** argv )
{
    return 0;
}


// EOF
