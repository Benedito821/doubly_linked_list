#ifndef LISTS_H_INCLUDED
#define LISTS_H_INCLUDED


typedef struct List
{
    void  *priv;

    char* (*get_node_string_by_index)(struct List *_list,int index);
    int   (*get_list_size) (struct List *_list);

    void (*add_node_at_end) (struct List *_list,char *_string);
    void (*add_node_at_begin)(struct List *_list,char *_string);
    void (*add_node_by_index) (struct List *_list,char *_string,int index);

    void (*delete_node_at_begin)(struct List *_list);
    void (*delete_node_at_end) (struct List *_list);
    void (*delete_node_by_index) (struct List *_list,int index);
}ts_list;

ts_list* create_list(void);
void delete_list(ts_list **_list);

#endif
