//Guilherme Bortoletto
//Ryan Sakurai
//Vinicius Castro

#include "stack.h"

#define INVALID -1


void stack_init(Stack *stack) {
    stack->array_size = 1;
    stack->array = malloc(stack->array_size * sizeof(U));
    stack->top_index = INVALID;
}


void stack_destroy(Stack *stack) {
    free(stack->array);
}


bool is_array_full(Stack *stack) {
    return stack->array_size == stack_get_size(stack);
}


void stack_push(Stack *stack, U data) {
    if(is_array_full(stack)) {
        stack->array_size *= 2;
        stack->array = realloc(stack->array, stack->array_size * sizeof(U));
    }

    stack->top_index++;
    stack->array[stack->top_index] = data;
}


bool is_array_too_big(Stack *stack) {
    return stack->array_size > 1 && stack_get_size(stack) <= stack->array_size/4;
}


bool stack_pop(Stack *stack, U *output) {
    if(!stack_is_empty(stack)) {
        *output = stack->array[stack->top_index];
        stack->top_index--;

        if(is_array_too_big(stack)) {
            stack->array_size /= 2;
            stack->array = realloc(stack->array, stack->array_size * sizeof(U));
        }

        return true;
    }
    else {
        return false;
    }
}


bool stack_get_top(Stack *stack, U *output) {
    if(!stack_is_empty(stack)) {
        *output = stack->array[stack->top_index];
        return true;
    }
    else {
        return false;
    }
}


unsigned stack_get_size(Stack *stack) {
    return stack->top_index + 1;
}


bool stack_is_empty(Stack *stack) {
    return stack_get_size(stack) <= 0;
