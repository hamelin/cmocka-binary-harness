#ifndef INC_CTEST_H
#define INC_CTEST_H

#ifndef TEST_NAME
#error "Macro TEST_NAME not set prior to writing up the unit tests. Set this to the name of the unit test module."
#endif

#include <stdlib.h>

#define SETUP()     void setup_cmocka__##TEST_NAME( void* state )
#define TEARDOWN()  void teardown_cmocka__##TEST_NAME( void* state )
#define TEST(name)  void test_cmocka__##TEST_NAME##__##name( void* state )

extern void* ptr_freed_last;


#endif  // INC_CTEST_H
