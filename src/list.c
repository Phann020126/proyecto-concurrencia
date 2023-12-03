#include "list.h"
#include "pthread.h"
#include "stdio.h"
#include "stdlib.h"

int size = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Add node
void add_node(int_ll_t *out_node, int_ll_t *next, int value)
{
    out_node = (int_ll_t *)malloc(sizeof(int_ll_t));
    out_node->value = value;
    out_node->next = next;
    pthread_mutex_init(&out_node->mutex, NULL); 
}

// Init list structure
int init_list(int_ll_t *list)
{
    add_node(list, NULL, 1);
    return 0;
}

// Free list structure
int free_list(int_ll_t *list)
{
    while(list->next)
    {
        free_list(list->next);
    }
    free(list);

    return 0;
}

// Get list size
int size_list(int_ll_t *list)
{
    return size;
}

// Get element at index
int index_list(int_ll_t *list, int index, int *out_value)
{
    if(index = -1 || index >= size) return 1;

    int_ll_t *node = list;

    while (index != 0)
    {
        node = node->next;
        index--;
    }

    *out_value = node->value;

    return 0;
}

// Insert element at index
int insert_list(int_ll_t *list, int index, int value)
{
    if(index = -1 || index >= size) return 1;

    int_ll_t *node = list;
    int_ll_t *new;

    while(index != 0)
    {
        node = node->next;
        index--;
    }

    add_node(new, node->next, value);
    
    node->next = new;
    size += 1;

    return 0;
}

// Remove element at index
int remove_list(int_ll_t *list, int index, int *out_value)
{
    if(index = -1 || index >= size)
    {
        *out_value = 1;
        return 1;
    }

    int_ll_t *node = list;
    
    if(index == 0)
    {
        list = list->next;
        free(node);

        return 0;
    }

    while(index != 1)
    {
        node = list->next;
        index--;
    }

    int_ll_t *old = node->next;
    node->next = node->next->next;
    
    free(old);

    size -= 1;

    return 0;
}
