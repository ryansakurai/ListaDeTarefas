/**
 * API for a stack
 * 
 * Authors
 * - Guilherme Bortoletto
 * - Ryan Sakurai
 * - Vinicius Castro
 */

#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdbool.h>
#include "macros.h"

typedef Change U;


typedef struct Stack
{
    U *array;
    unsigned first_empty_index;
    unsigned array_size;
} Stack;


/**
 * Initializes the stack
 * 
 * Parameters
 * - Stack *stack
 * 
 * Returns: void
 */
void stack_init(Stack *stack);


/**
 * Destroys the stack
 * 
 * Parameters
 * - Stack *stack
 * 
 * Returns: void
 */
void stack_destroy(Stack *stack);


/**
 * Pushes an item to the list
 * 
 * Parameters
 * - Stack *stack
 * - U data: item to be pushed
 * 
 * Returns: void
 */
void stack_push(Stack *stack, U data);


/**
 * Pops an item and stores it in a variable
 * 
 * Parameters
 * - Stack *stack
 * - U *output: variable where the item will be stored
 * 
 * Returns: bool
 * - If it was possible to pop an item
 */
bool stack_pop(Stack *stack, U *output);


/**
 * Stores the top item of the stack in a variable
 * 
 * Parameters
 * - Stack *stack
 * - U *output: variable where the item will be stored
 * 
 * Returns: bool
 * - True if it was possible to get the item
 * - False if the stack is empty and it wasn't possible
 */
bool stack_get_top(Stack *stack, U *output);


/**
 * Returns the size of the stack
 * 
 * Parameters
 * - Stack *stack
 * 
 * Returns: unsigned
 * - The size of the stack
 */
unsigned stack_get_size(Stack *stack);


/**
 * Returns if the stack is empty
 * 
 * Parameters
 * - Stack *stack
 * 
 * Returns: bool
 * - If the stack is empty
 */
bool stack_is_empty(Stack *stack);


#endif
