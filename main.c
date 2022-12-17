/**
 * Implements a task list
 * 
 * - Sorted by priority
 * - Supports adding task, removing task and undoing action
 * 
 * Authors
 * - Guilherme Bortoletto
 * - Ryan Sakurai
 * - Vinicius Castro
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "libs/macros.h"
#include "libs/ordered_list.h"
#include "libs/stack.h"


#define STR_LEN 100


bool str_is_num(const char *string) {
    if(strlen(string) > 0) {
        for(int i=0; i < STR_LEN && string[i] != '\0'; i++)
            if(!isdigit(string[i]))
                return false;
        return true;
    }
    else {
        return false;
    }
}


void str_to_lower(char *string) {
    for(int i=0; i < STR_LEN && string[i] != '\0'; i++)
        if(isupper(string[i]))
            string[i] = tolower(string[i]);
}


void input(const char *command, char *output) {
    char c;
    int i_char;

    printf(command);
    for(i_char=0; (c = getchar()) != '\n' && c != EOF; i_char++)
        output[i_char] = c;

    output[i_char] = '\0';
}


void print_list(OrderedList list) {
    OLIterator iter;
    if(ol_iter_init(&iter, &list)) {
        unsigned index = 1;
        do {
            Task task;
            ol_get_current_item(&iter, &task);
            printf("%u. %s\n", index, task.description);
            index++;
        } while(ol_iter_next(&iter));
    }
    else {
        printf("The list is empty.\n");
    }
}


int read_option() {
    while(true) {
        printf("[0] Exit program\n");
        printf("[1] Add task\n");
        printf("[2] Remove task\n");
        printf("[3] Undo\n");

        char option_str[STR_LEN];
        input("Option: ", option_str);

        if(str_is_num(option_str)) {
            int option = atoi(option_str);
            if(option >= 0 && option <= 3)
                return option;
        }

        printf("Invalid option!\n\n");
    }
}


void read_description(char *output) {
    while(true) {
        input("Task: ", output);
        if(strlen(output) <= 0)
            printf("Invalid description!\n");
        else
            break;
    }
}


void read_priority(Level *output) {
    while(true) {
        char priority[100];
        input("Priority (low/mid/high): ", priority);
        str_to_lower(priority);

        if(strcmp("low", priority) == 0) {
            *output = LOW;
            break;
        }
        else if(strcmp("mid", priority) == 0) {
            *output = MID;
            break;
        }
        else if(strcmp("high", priority) == 0) {
            *output = HIGH;
            break;
        }
        else {
            printf("Invalid priority level!\n");
        }
    }
}


void add_change(Stack *changes, Action description, Task target) {
    Change change;
    change.description = description;
    change.target = target;
    stack_push(changes, change);
}


int read_task_to_remove(OrderedList list) {
    while(true) {
        char i_task_str[STR_LEN];
        input("Task index: ", i_task_str);

        if(str_is_num(i_task_str)) {
            int i_task = atoi(i_task_str);
            if(i_task > 0 && i_task <= ol_get_size(&list))
                return i_task;
        }

        printf("Invalid option!\n\n");
    }
}


void update_indexes(OrderedList *list) {
    int index = 1;
    OLIterator iter;
    if(ol_iter_init(&iter, list))
        do {
            iter.current_item->data.index = index++;
        } while(ol_iter_next(&iter));
}


bool is_task_index_equal(void *a, void *b) {
    return ((Task*) a)->index == ((Task*) b)->index;
}


Task remove_task(OrderedList *task_list, int index) {
    OLIterator iter;
    ol_iter_init(&iter, task_list);
    ol_search(&iter, &is_task_index_equal, &index);
    Task task;
    ol_pop_current_item(&iter, &task);
    return task;
}


bool move_down(void *a, void *b) {
    if(((Task*) a)->priority < ((Task*) b)->priority)
        return true;
    else if(((Task*) a)->priority == ((Task*) b)->priority && difftime(((Task*) a)->addition_moment, ((Task*) b)->priority) > 0)
        return true;
    else
        return false;
}


int main() {
    OrderedList task_list;
    Stack changes;
    ol_init(&task_list, &move_down);
    stack_init(&changes);

    while(true) {
        printf("TASK LIST\n\n");
        print_list(task_list);
        printf("\n");

        int option = read_option();
        printf("\n");
        if(option == 0) { //exit program
            break;
        }
        else if(option == 1) { //add task
            Task task;
            task.addition_moment = time(NULL);
            read_description(task.description);
            printf("\n");
            read_priority(&task.priority);
            
            ol_push(&task_list, task);
            add_change(&changes, ADDITION, task);
        }
        else if(option == 2) { //remove task
            int index = read_task_to_remove(task_list);
            Task task = remove_task(&task_list, index);
            add_change(&changes, REMOVAL, task);
        }
        else { //undo
            Change change;
            stack_pop(&changes, &change);
            if(change.description == ADDITION)
                remove_task(&task_list, change.target.index);
            else
                ol_push(&task_list, change.target);
            printf("There you go, undone!\n");
        }

        update_indexes(&task_list);
        printf("\n-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-\n\n");
    }

    ol_destroy(&task_list);
    stack_destroy(&changes);

    return 0;
}
