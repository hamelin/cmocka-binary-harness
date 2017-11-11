#ifndef LIST_H__
#define LIST_H__

#include <stdbool.h>


typedef struct _list_node
{
    void* content;
    struct _list_node* next;
} list_node;
#define NODE_NIL   { NULL, NULL };
list_node* list_node_alloc();
void list_node_free( list_node** pn );
#define list_node_get_content( n )   ( (n)->content )
#define list_node_get_next( n )      ( (n)->next )


typedef void (*fn_list_free_node_content)( void** p );
void free_malloc( void** p );
typedef bool (*fn_match_node_content)( const void* ref, const void* obj );


typedef struct _list
{
    list_node* head;
    fn_list_free_node_content free;
} list;
#define LIST_NIL   { NULL, NULL }
list* list_alloc();
void list_free( list** pll );
list* list_init( list* ll, fn_list_free_node_content ff );
void list_push( list* ll, void* obj );
const void* list_lookup( list* ll, fn_match_node_content is_match, const void* obj );
#define as_obj( num )          ( (const void*)( num ) )
#define list_make_iter( ll )   (ll)->head


typedef list_node list_iter;
#define list_iter_free( i )
#define list_iter_is_at_end( i )  ( !( i ) )
#define list_iter_get( i )        list_node_get_content( i )
#define list_iter_next( i )       ( (i) = list_node_get_next( (i) ) )


#endif  // LIST_H__
