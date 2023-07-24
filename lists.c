#include <stdio.h>
#include <stdlib.h>
#include "lists.h"
#define EMPTY_LIST(size) (size==0)
#define VALID_INDEX(index) (index>=0&&index<size)
#define FIRST_NODE(index) (index==0)
#define LAST_NODE(index,size) (index==size-1)
#define MANY_NODES(size) (size > 1)

typedef struct list_node
{
    char *string;
    struct list_node *next;
    struct list_node *previous;
}ts_node;

typedef struct list_data
{
    int  size;
    ts_node *first;
    ts_node *last;
}ts_priv_list_data;


char* get_node_string_by_index(ts_list *list,int index);
int  get_list_size(ts_list *list);
ts_node* get_node_at_index(ts_list* list,int index);
ts_node* get_first_of_list(ts_list* list);
void set_list_size(ts_list* list,int val);
void add_node_at_end(ts_list *list,char *string);
void add_node_at_begin(ts_list *list,char *string);
void add_node_by_index(ts_list *list,char *string,int index);
void delete_node_at_begin(ts_list *list);
void delete_node_at_end(ts_list *list);
void delete_node_by_index(ts_list *list,int index);

ts_list* create_list(void)
{
    ts_list* new_list = (ts_list*)malloc(sizeof(ts_list));
    if(new_list==NULL)
        return NULL;
    *new_list = (ts_list){
        .priv = (ts_priv_list_data*)calloc(1,sizeof(ts_priv_list_data)),
        .get_node_string_by_index = get_node_string_by_index,
        .get_list_size = get_list_size,
        .add_node_at_end = add_node_at_end,
        .add_node_at_begin = add_node_at_begin,
        .add_node_by_index = add_node_by_index,
        .delete_node_at_begin = delete_node_at_begin,
        .delete_node_at_end = delete_node_at_end,
        .delete_node_by_index = delete_node_by_index
    };
    return new_list;
}


void delete_node_at_begin(ts_list *list)
{
    int size = get_list_size(list);
    if(EMPTY_LIST(size))
        return;
    ts_priv_list_data* list_control = list->priv;
    ts_node* aux_ptr_first = list_control->first;
    ts_node * aux_head = list_control->first;
    if(MANY_NODES(size))
    {
        list_control->first = aux_ptr_first->next;
        //list_control->first->previous = NULL;
        aux_head->previous = NULL;
    }
    free(aux_ptr_first);
    set_list_size(list,size-1);
    return;
}

void delete_node_at_end(ts_list *list)
{
    int size = get_list_size(list);
    if(!EMPTY_LIST(size))
    {
        ts_priv_list_data* list_control = list->priv;
        ts_node* aux_ptr_last = list_control->last;
        ts_node* aux_tail = list_control->last;
        if(MANY_NODES(size))
        {
            list_control->last = aux_ptr_last->previous;
            //(list_control->last)->next = NULL;
            aux_tail->next = NULL;
        }
        free(aux_ptr_last);
        set_list_size(list,size-1);
    }
    return;
}

void delete_node_by_index(ts_list *list,int index)
{
    int size = get_list_size(list);
    if(EMPTY_LIST(size))
        return;
//    if(VALID_INDEX(index))
//    {
        if(FIRST_NODE(index))
            delete_node_at_begin(list);
        else if(LAST_NODE(index,size))
            delete_node_at_end(list);
        else
        {
            ts_node* current_node = get_node_at_index(list,index);
            ts_node* previous_node = get_node_at_index(list,index-1);
            ts_node* next_of_current_node = current_node->next;
            previous_node->next = current_node->next;
            //(current_node->next)->previous = previous_node;
            next_of_current_node->previous = previous_node;
            free(current_node);
            set_list_size(list,size-1);
        }
   // }
    return;
}

void delete_list(ts_list** list)
{
   // if(*list==NULL)
   //     return;
    int size = get_list_size(*list);
    int index = 0;
    for(index = 0;index<size;index++)
        delete_node_by_index(*list,index);
    free((*list)->priv);
    free(*list);
    list = NULL;
    return;
}

void set_list_size(ts_list* list,int val)
{
    ((ts_priv_list_data*)(list->priv))->size = val;
}

int get_list_size(ts_list *list)
{
    return ((ts_priv_list_data*)(list->priv))->size;
}

ts_node* get_first_of_list(ts_list* list)
{
    return ((ts_priv_list_data*)(list->priv))->first;
}

ts_node* get_last_of_list(ts_list* list)
{
    return ((ts_priv_list_data*)(list->priv))->last;
}

ts_node* get_node_at_index(ts_list* list,int index)
{
    int size = get_list_size(list);
    //if(EMPTY_LIST(size)||!VALID_INDEX(index))
    if(EMPTY_LIST(size))
        return NULL;
    ts_node* first = get_first_of_list(list);
    ts_node* ptr = first;
    int cont = 0;
    for(cont = 0;cont<index;cont++)
        ptr = ptr->next;
    return ptr;
}

char* get_node_string_by_index(ts_list* list,int index)
{
    int size = get_list_size(list);
   //if(EMPTY_LIST(size)||!VALID_INDEX(index))
    if(EMPTY_LIST(size))
        return NULL;
    ts_node* first = get_first_of_list(list);
    ts_node* ptr = first;
    int cont;
    for(cont = 0;cont<index;cont++)
        ptr = ptr->next;
    return ptr->string;
}

void add_node_by_index(ts_list* list,char* string,int index)
{
    int size = get_list_size(list);
    if(MANY_NODES(size))
    {
        ts_node* current_node = get_node_at_index(list,index);
        if(FIRST_NODE(index))
        {
            add_node_at_begin(list,string);
            return;
        }
        if(current_node!=NULL)
        {
            ts_node* previous_node = get_node_at_index(list,index-1);

            ts_node* new_node = (ts_node*)malloc(sizeof(ts_node));

            new_node->string = string;
            previous_node->next = new_node;
            new_node->previous = previous_node;
            new_node->next = current_node;
            current_node->previous = new_node;
            set_list_size(list,size+1);
        }
    }
    return;
}

void add_node_at_begin(ts_list *list,char *string)
{
        ts_node* new_node = (ts_node*)malloc(sizeof(ts_node));
        ts_priv_list_data* list_control = list->priv;
        ts_node* first = list_control->first;
        int size = get_list_size(list);

        if(new_node==NULL)
            return;

        if(EMPTY_LIST(size))
            list_control->last = new_node;
        else first->previous = new_node;

        new_node->next = list_control->first;
        list_control->first = new_node;
        new_node->string=string;
        new_node->previous = NULL;
        set_list_size(list,size+1);

        return;
}

void add_node_at_end(ts_list* list,char* string)
{
    ts_node* new_node = (ts_node*)malloc(sizeof(ts_node));
    ts_priv_list_data *list_control = list->priv;
    ts_node *last = list_control->last;
    int size = get_list_size(list);

    if(new_node == NULL)
        return;

    if(EMPTY_LIST(size))
        list_control->first = new_node;
    else last->next = new_node;

    new_node->previous = list_control->last;
    list_control->last = new_node;
    new_node->string = string;
    new_node->next = NULL;
    set_list_size(list,size+1);

    return;
}
