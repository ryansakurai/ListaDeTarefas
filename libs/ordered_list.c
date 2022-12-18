//Guilherme Bortoletto
//Ryan Sakurai
//Vinicius Castro

#include "ordered_list.h"


void ol_init(OrderedList *list, bool (*move_down)(void *a, void *b)) {
    list->sentinel = malloc(sizeof(OLNode));
    list->sentinel->prev = list->sentinel->next = list->sentinel;
    list->size = 0;
    list->move_down = move_down;
}


void ol_destroy(OrderedList *list) {
    while(!ol_is_empty(list))
        ol_pop_first(list, NULL);
    
    free(list->sentinel);
    list->sentinel = NULL;
}


bool end_reached(OLIterator iter) {
    return iter.current_item->next == iter.list->sentinel;
}


void ol_push(OrderedList *list, T data) {
    OLNode *new_node = malloc(sizeof(OLNode));
    new_node->data = data;

    OLIterator iter;
    if(ol_iter_init(&iter, list)) {
        while((*list->move_down)(&new_node->data, &iter.current_item->data) && ol_iter_next(&iter));

        if(end_reached(iter) && (*list->move_down)(&new_node->data, &iter.current_item->data)) {
            // places after current_item
            new_node->prev = iter.current_item;
            new_node->next = iter.current_item->next;
            new_node->next->prev = new_node;
            new_node->prev->next = new_node;
        }
        else {
            // places before current_item
            new_node->prev = iter.current_item->prev;
            new_node->next = iter.current_item;
            new_node->next->prev = new_node;
            new_node->prev->next = new_node;
        }
    }
    else {
        new_node->next = new_node->prev = list->sentinel;
        new_node->next->prev = new_node;
        new_node->prev->next = new_node;
    }
    
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
    return list->size <= 0;
}


bool ol_iter_init(OLIterator *iter, OrderedList *list) {
    if(!ol_is_empty(list)) {
        iter->list = list;
        iter->current_item = list->sentinel->next;
        return true;
    }
    else {
        return false;
    }
}


bool ol_iter_next(OLIterator *iter) {
    if(!end_reached(*iter)) {
        iter->current_item = iter->current_item->next;
        return true;
    }
    else {
        return false;
    }
}

bool is_in_range(OLIterator *iter) {
    return iter->current_item != iter->list->sentinel;
}


bool ol_get_current_item(OLIterator *iter, T *output) {
    if(is_in_range(iter)) {
        *output = iter->current_item->data;
        return true;
    }
    else {
        return false;
    }
}


bool ol_pop_current_item(OLIterator *iter, T *output) {
    if(is_in_range(iter)) {
        OLNode *popped = iter->current_item;
        *output = popped->data;

        popped->prev->next = popped->next;
        popped->next->prev = popped->prev;
        iter->current_item = iter->current_item->next;
        free(popped);
        iter->list->size--;

        return true;
    }
    else {
        return false;
    }
}


bool ol_search(OLIterator *iter, bool (*equals)(void *a, void *b), T key) {
    OLIterator private_iter;
    if(ol_iter_init(&private_iter, iter->list))
        do {
            if((*equals)(&key, &private_iter.current_item->data)) {
                iter->current_item = private_iter.current_item;
                return true;
            }
        } while(ol_iter_next(&private_iter));

    return false;
}
