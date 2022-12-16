/**
 * API for an ordered list in descending order
 * 
 * Authors
 * - Guilherme Bortoletto
 * - Ryan Sakurai
 * - Vinicius Castro
 */

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
 * Initializes the list
 * 
 * Parameters
 * - OrderedList *list
 * - int (*compare)(void *a, void *b): function used to sort the list (returns negative if a<b, positive if a>b and zero if a==b)
 * 
 * Returns: void
 */
void ol_init(OrderedList *list, int (*compare)(void *a, void *b));


/**
 * Destroys the list
 * 
 * Parameters
 * - OrderedList *list
 * 
 * Returns: void
 */
void ol_destroy(OrderedList *list);


/**
 * Pushes an item to the list, following its order
 * 
 * Parameters
 * - OrderedList *list
 * - T data: data to be pushed to the list
 * 
 * Returns: void
 */
void ol_push(OrderedList *list, T data);


/**
 * Pops the first item off the list and stores it in a variable
 * 
 * Parameters
 * - OrderedList *list
 * - T *output: variable where the popped item will be stored
 * 
 * Returns: bool
 * - If it was possible to pop an item
 */
bool ol_pop_first(OrderedList *list, T *output);


/**
 * Pops the last item off the list and stores it in a variable
 * 
 * Parameters
 * - OrderedList *list
 * - T *output: variable where the popped item will be stored
 * 
 * Returns: bool
 * - If it was possible to pop an item
 */
bool ol_pop_last(OrderedList *list, T *output);


/**
 * Stores the first item of the list in a variable
 * 
 * Parameters
 * - OrderedList *list
 * - T *output: variable where the item will be stored
 * 
 * Returns: bool
 * - If it was possible to get the item
 */
bool ol_get_first(OrderedList *list, T *output);


/**
 * Stores the last item of the list in a variable
 * 
 * Parameters
 * - OrderedList *list
 * - T *output: variable where the item will be stored
 * 
 * Returns: bool
 * - If it was possible to get the item
 */
bool ol_get_last(OrderedList *list, T *output);


/**
 * Returns the size of the list
 * 
 * Parameters
 * - OrderedList *list
 * 
 * Returns: unsigned
 * - The size of the list
 */
unsigned ol_get_size(OrderedList *list);


/**
 * Returns if the list is empty
 * 
 * Parameters
 * - OrderedList *list
 * 
 * Returns: bool
 * - If the list is empty
 */
bool ol_is_empty(OrderedList *list);


/**
 * Initializes the iterator in a list
 * 
 * Parameters
 * - OLIterator *iter
 * - OrderedList *list: list the iterator will point to
 * 
 * Returns: bool
 * - True if it was possible to initialize it
 * - False if the list is empty and it wasn't possible
 */
bool ol_iter_init(OLIterator *iter, OrderedList *list);


/**
 * Returns if the iterator is linked to the list
 * 
 * Parameters
 * - OLIterator *iter
 * - OrderedList *list: list to verify link
 * 
 * Returns: bool
 * - If it's linked to the list
 */
bool ol_iter_is_linked(OLIterator *iter, OrderedList *list);


/**
 * Moves the iterator to the next item in the list
 * 
 * Parameters
 * - OLIterator *iter
 * 
 * Returns: bool
 * - True if it was possible
 * - False if the end of the list was reached and it wasn't possible
 */
bool ol_iter_next(OLIterator *iter);


/**
 * Returns the element currently being pointed by the iterator
 * 
 * Parameters
 * - OLIterator *iter
 * 
 * Returns: T
 * - The data of the element
 */
T ol_get_current(OLIterator *iter);


/**
 * Pops and returns the the element currently being pointed by the iterator
 * 
 * Parameters
 * - OLIterator *iter
 * 
 * Returns: T
 * - The data of the element
 */
T ol_pop_current(OLIterator *iter);


/**
 * Moves the iterator to a certain item, if it's possible to find it
 * 
 * Parameters
 * - OrderedList *iter
 * - int (*compare)(void *a, void *b): function used to find the item (returns negative if a<b, positive if a>b and zero if a==b)
 * - T data: data of the item to be searched for
 * 
 * Returns: bool
 * - If it was possible to find it
 */
bool ol_search(OLIterator *iter, int (*compare)(void *a, void *b), T data);


#endif
