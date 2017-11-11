list_node* list_node_alloc()
{
    list_node nil = NODE_NIL;
    list_node* node = calloc( 1, sizeof( list_node ) );
    memcpy( node, &nil, sizeof( list_node ) );
    return node;
}


void list_node_free( list_node** pnode )
{
    if( *pnode )
    {
        free( *pnode );
        *pnode = NULL;
    }
}


list* list_alloc()
{
    list nil = LIST_NIL;
    list* ll = calloc( 1, sizeof( list ) );
    memcpy( ll, &nil, sizeof( list ) );
    return ll;
}


list* list_init( list* ll, fn_list_free_node_content ff )
{
    ll->head = NULL;
    ll->free = ff;
    return ll;
}


void list_free( list** pll )
{
    if( *pll )
    {
        list_node* current = (*pll)->head;
        list_node* to_free;

        while( current )
        {
            to_free = current;
            current = list_node_get_next( current );
            if( (*pll)->free )
            {
                (*pll)->free( &list_node_get_content( to_free ) );
            }
            list_node_free( &to_free );
        }

        free( *pll );
        *pll = NULL;
    }
}


void list_push( list* ll, void* obj )
{
    list_node* node_new = list_node_alloc();
    node_new->content = obj;
    node_new->next = ll->head;
    ll->head = node_new;
}


void* list_lookup( list* ll, fn_match_node_content is_match, const void* obj )
{
    list_iter* iter;
    void* match = NULL;
    for( iter = list_make_iter( ll ); !list_iter_is_at_end( iter ); list_iter_next( iter ) )
    {
        void* cur = list_iter_get( iter );
        if( is_match( cur, obj ) )
        {
            match = cur;
            break;
        }
    }
    return match;
}


void free_malloc( void** p )
{
    if( *p )
    {
        free( *p );
        *p = NULL;
    }
}
