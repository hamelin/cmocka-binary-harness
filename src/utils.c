void field_free( char** field )
{
    if( *field )
    {
        free( *field );
        *field = NULL;
    }
}


void field_set_string( char** field, const char* value )
{
    field_free( field );
    if( value && strlen( value ) > 0 )
    {
        *field = strdup( value );
    }
}


char* skip_blank( char** s )
{
    while( **s != 0 && ( **s == ' ' || **s == '\t' ) )
    {
        ++(*s);
    }
    return *s;
}
