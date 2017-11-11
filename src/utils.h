#ifndef UTILS_H__
#define UTILS_H__

#include <stdbool.h>

#define LEN_STATIC_ARRAY( ar )    ( sizeof( ar ) / sizeof( (ar)[0] ) )
#define LEN_STATIC_ZARRAY( ar )   ( LEN_STATIC_ARRAY( ar ) - 1 )
void field_free( char** field );
void field_set_string( char** field, const char* value );

char* skip_blank( char** s );

#endif  // UTILS_H__
