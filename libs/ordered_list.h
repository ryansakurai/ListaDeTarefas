//Guilherme Bortoletto
//Ryan Sakurai
//Vinicius Castro

#ifndef ORDERED_LIST_H
#define ORDERED_LIST_H

#include <stdlib.h>
#include <stdbool.h>
#include "macros.h"

typedef Task T;


typedef struct OLNode {
    T data;
    struct OLNode *prev;
    struct OLNode *next;
} OLNode;

typedef struct OrderedList {
    OLNode *sentinel;
    unsigned size;
    int (*compare)(void *a, void *b);
} OrderedList;

typedef struct OLIterator {
    OrderedList *list;
    OLNode *current;
} OLIterator;


/**
 * 
 */
void ol_init(OrderedList *list, int (*compare)(void *a, void *b));


/**
 * 
 */
void ol_destroy(OrderedList *list);


/**
 * 
 */
void ol_push(OrderedList *list, T data);


/**
 * 
 */
T ol_pop_first(OrderedList *list);


/**
 * 
 */
T ol_pop_last(OrderedList *list);


/**
 * 
 */
T ol_get_first(OrderedList *list);


/**
 * 
 */
T ol_get_last(OrderedList *list);


/**
 * 
 */
unsigned ol_get_size(OrderedList *list);


/**
 * 
 */
bool ol_is_empty(OrderedList *list);


/**
 * 
 */
void ol_iter_init(OLIterator *iter, OrderedList *list);


/**
 * 
 */
void ol_iter_next(OLIterator *iter);


/**
 * 
 */
bool ol_search(OLIterator *iter, int (*compare)(void *a, void *b), T data);


/**
 * 
 */
T ol_get_current(OLIterator *iter);


/**
 * 
 */
T ol_pop_current(OLIterator *iter);


#endif
