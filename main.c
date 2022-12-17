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
#include "libs/macros.h"
#include "libs/ordered_list.h"
#include "libs/stack.h"


#define STR_LEN 100


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


char read_option() {
    while(true) {
        printf("[0] Exit program\n");
        printf("[1] Add task\n");
        printf("[2] Remove task\n");
        printf("[3] Undo\n");

        int option;
        printf("Option: ");
        scanf("%d", &option);

        if(option >= 0 && option <= 3)
            return option;
        else
            printf("Invalid option!\n\n");
    }
}


void str_to_lower(char *string) {
    for(int i=0; i < STR_LEN && string[i] != '\0'; i++)
        if(isupper(string[i]))
            string[i] = tolower(string[i]);
}


char* read_description() {
    char description[100];
    scanf("%s\n", description);
    if(strlen(description) > 0)
        return description;
    else
        printf("Invalid description!\n");
}


Level read_priority() {
    while(true) {
        char priority[100];
        scanf("%s\n", priority);
        str_to_lower(priority);
        if(strcmp("low", priority))
            return LOW;
        else if(strcmp("mid", priority))
            return MID;
        else if(strcmp("high", priority))
            return HIGH;
        else
            printf("Invalid priority level!\n");
    }
}


Task read_task_to_add() {
    Task task;
    
    printf("Task: ");
    strcpy(task.description, read_description());
    printf("\n");
    
    printf("Priority (low/mid/high): ");
    task.priority = read_priority();

    return task;
}


void add_change(Stack *changes, Action description, Task target) {
    Change change;
    change.description = description;
    change.target = target;
    stack_push(changes, change);
}


bool str_is_num(char *string) {
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


int read_task_to_remove(OrderedList list) {
    while(true) {
        char i_task_str[STR_LEN];
        printf("Task index: ");
        scanf("%s\n", i_task_str);

        if(str_is_num(i_task_str)) {
            int i_task = atoi(i_task_str);
            if(i_task > 0 && i_task <= ol_get_size(&list))
                return i_task;
        }

        printf("Invalid option!\n\n");
    }
}


bool is_task_index_equal(void *a, void *b) {
    return ((Task*) a)->index == ((Task*) b)->index;
}


Task remove_task(OrderedList *task_list, int index) {
    OLIterator iter;
    ol_search(&iter, &is_task_index_equal, &index);
    Task task;
    ol_pop_current_item(&iter, &task);
    return task;
}


int compare_tasks(void *a, void *b) {
    return ((Task*) a)->priority - ((Task*) b)->priority;
}


int main() {
    OrderedList task_list;
    Stack changes;
    ol_init(&task_list, &compare_tasks);
    stack_init(&changes);

    while(true) {
        printf("TASK LIST\n\n");
        print_list(task_list);
        printf("\n");

        int option = read_option();
        if(option == 0) { //exit program
            break;
        }
        else if(option == 1) { //add task
            Task task = read_task_to_add();
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
        }
    }

    ol_destroy(&task_list);
    stack_destroy(&changes);

    return 0;
}
