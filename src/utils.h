#ifndef UTILS_H__
#define UTILS_H__

#include <stdbool.h>

void field_free( char** field );
void field_set_string( char** field, const char* value );

char* skip_blank( char** s );

#endif  // UTILS_H__
