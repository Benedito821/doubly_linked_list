#include "main.h"

typedef enum options
{
    e_get_size,
    e_add_at_begin,
    e_add_at_end,
    e_add_by_index,
    e_delete_at_begin,
    e_delete_at_end,
    e_delete_by_index,
    e_show_list,
    e_exit
}te_options;

#define INITIAL_VALUE 1
int main()
{
    ts_list* new_list = create_list();
    if(!new_list)
        exit(2);
    int index = INITIAL_VALUE;
    int cont = INITIAL_VALUE;
    int size = new_list->get_list_size(new_list);
    while(1)
    {
        printf(" Wich operation?\n 0-get size\n 1-add at begin\n 2-add at end\n 3-add by index\n 4-delete at begin\n 5-delete at end\n 6-delete by index\n 7-show list\n 8-EXIT\n type command:");
        te_options option = read_command();
        if(option == e_get_size)
            printf("size = %d\n\n",new_list->get_list_size(new_list));
        if(option == e_add_at_begin)
        {
            printf("type string:");
            new_list->add_node_at_begin(new_list,read_strings());
            printf("string added\n");
        }
        if(option == e_add_at_end)
        {
            printf("type string:");
            new_list->add_node_at_end(new_list,read_strings());
            printf("string added\n");
        }
        if(option == e_add_by_index)
        {
            size = new_list->get_list_size(new_list);
            printf("which position:");
            scanf("%d",&index);
            if(VALID_INDEX(index))
            {
                printf("type string:");
                new_list->add_node_by_index(new_list,read_strings(),index);
                printf("string added\n");
            }
            else printf("Wrong index\n");
        }
        if(option == e_delete_at_begin)
        {
            size = new_list->get_list_size(new_list);
            if(!EMPTY_LIST(size))
            {
                new_list->delete_node_at_begin(new_list);
                printf("node deleted\n");
            }
            else printf("Empty list\n");
        }
        if(option == e_delete_at_end)
        {
            size = new_list->get_list_size(new_list);
            if(!EMPTY_LIST(size))
            {
                new_list->delete_node_at_end(new_list);
                printf("node deleted\n");
            }
            else printf("Empty list\n");
        }
        if(option == e_delete_by_index)
        {
            size = new_list->get_list_size(new_list);
            if(!EMPTY_LIST(size))
            {
                printf("which position:");
                scanf("%d",&index);
                if(VALID_INDEX(index))
                {
                   new_list->delete_node_by_index(new_list,index);
                   printf("node deleted\n");
                }
                else printf("Wrong index\n");
            }
            else printf("Empty list\n");
        }
        if(option == e_show_list)
        {
            size = new_list->get_list_size(new_list);
            if(!EMPTY_LIST(size))
                for(cont =0;cont < size;cont++)
                    printf("%s\n",new_list->get_node_string_by_index(new_list,cont));
            else printf("Empty list\n");
        }
        if(option == e_exit)
        {
            delete_list(&new_list);
            printf("                   BYE BYE ('_')");
            return 0;
        }
    }
    return 0;
}
