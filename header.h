#ifndef HEADER_H__
#define HEADER_H__

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cmp_stdio.h>

#include "ctest.h"

#define NO_SETUP()      setup_fn do_setup = NULL
#define SET_SETUP()     setup_fn do_setup = setup
#define NO_TEARDOWN()   teardown_fn do_teardown = NULL
#define SET_TEARDOWN()  teardown_fn do_teardown = teardown

#endif  // HEADER_H__
