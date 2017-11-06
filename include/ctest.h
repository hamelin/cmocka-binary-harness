#ifndef INC_CTEST_H
#define INC_CTEST_H

#include <stdlib.h>


typedef void (*setup_fn)();
typedef void (*teardown_fn)();
typedef void (*ctest_fn)();
typedef struct _named_test
{
    const char* name;
    ctest_fn test;
} ctest;


typedef struct _failure
{
    const char* file;
    unsigned int line;
} failure;
extern failure the_failure;


void _fail( const char* file, int line );
#define fail()  _fail( __FILE__, __LINE__ )


#endif  // INC_CTEST_H
