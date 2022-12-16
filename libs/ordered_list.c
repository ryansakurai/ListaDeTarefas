//Guilherme Bortoletto
//Ryan Sakurai
//Vinicius Castro

#include "ordered_list.h"


void ol_init(OrderedList *list, int (*compare)(void *a, void *b)) {
    list->sentinel->prev = list->sentinel->next = list->sentinel = malloc(sizeof(OLNode));
    list->size = 0;
    list->compare = compare;
}


void ol_destroy(OrderedList *list) {
    while(!ol_is_empty(list))
        ol_pop_first(list, NULL);
    
    free(list->sentinel);
    list->sentinel = NULL;
}


void ol_push(OrderedList *list, T data) {
    OLNode *new_node = malloc(sizeof(OLNode));
    new_node->data = data;

    OLIterator iter;
    for(ol_iter_init(&iter, list); (*list->compare)(&iter.current->data, &new_node->data) && ol_iter_next(&iter); );

    new_node->prev = iter.current;
    new_node->next = iter.current->next;
    new_node->next->prev = new_node;
    new_node->prev->next = new_node;
    list->size++;
}


bool ol_pop_first(OrderedList *list, T *output) {
    if(!ol_is_empty(list)) {
        OLNode *popped = list->sentinel->next;
        if(output)
            *output = popped->data;

        list->sentinel->next = popped->next;
        list->sentinel->next->prev = list->sentinel;
        free(popped);
        list->size--;

        return true;
    }
    else {
        return false;
    }
}


bool ol_pop_last(OrderedList *list, T *output) {
    if(!ol_is_empty(list)) {
        OLNode *popped = list->sentinel->prev;
        if(output)
            *output = popped->data;

        list->sentinel->prev = popped->prev;
        list->sentinel->prev->next = list->sentinel;
        free(popped);
        list->size--;

        return true;
    }
    else {
        return false;
    }
}


bool ol_get_first(OrderedList *list, T *output) {
    if(!ol_is_empty(list)) {
        *output = list->sentinel->next->data;
        return true;
    }
    else {
        return false;
    }
}


bool ol_get_last(OrderedList *list, T *output) {
    if(!ol_is_empty(list)) {
        *output = list->sentinel->prev->data;
        return true;
    }
    else {
        return false;
    }
}


unsigned ol_get_size(OrderedList *list) {
    return list->size;
}


bool ol_is_empty(OrderedList *list) {
    if(list->size > 0)
        return false;
    else
        return true;
}


bool ol_iter_init(OLIterator *iter, OrderedList *list) {
    if(!ol_is_empty(list)) {
        iter->list = list;
        iter->current = list->sentinel->next;
        return true;
    }
    else {
        return false;
    }
}


bool ol_iter_is_linked(OLIterator *iter, OrderedList *list) {
    return iter->list == list && iter->current != list->sentinel;
}


bool ol_iter_next(OLIterator *iter) {
    if(iter->current->next != iter->list->sentinel) {
        iter->current = iter->current->next;
        return true;
    }
    else {
        return false;
    }
}


T ol_get_current(OLIterator *iter) {
    return iter->current->data;
}


T ol_pop_current(OLIterator *iter) {
    OLNode *popped = iter->current;
    T return_value = popped->data;

    popped->prev->next = popped->next;
    popped->next->prev = popped->prev;
    iter->current = iter->current->next;
    free(popped);
    iter->list->size--;

    return return_value;
}


bool ol_search(OLIterator *iter, int (*compare)(void *a, void *b), T data) {
    OLIterator private_iter;
    for(ol_iter_init(&private_iter, iter->list); ol_iter_next(&private_iter); )
        if((*compare)(&data, &private_iter.current->data) == 0) {
            iter->current = private_iter.current;
            return true;
        }

    return false;
}
