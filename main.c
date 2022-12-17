//Guilherme Bortoletto
//Ryan Sakurai
//Vinicius Castro

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h> //gtk3
#include "macros.h"
#include "ordered_list.h"
#include "stack.h"


GtkWidget *window;
GtkWidget *container;
GtkWidget *display_frame, *controls_frame;
GtkWidget *scrolled_window, *button_box;
GtkWidget *tasks, *priority_options, *add_input, *remove_input, *add_button, *remove_button, *undo_button;
GtkTextBuffer *buffer;
/*
 *  WIDGET HIERARCHY
 *
 *  window
 *      container
 *          display_frame
 *              scrolled_window
 *                  tasks
 *          controls_frame
 *              button_box
 *                  priority_options
 *                  add_input
 *                  remove_input
 *                  add_button
 *                  remove_button
 *                  undo_button
 */


typedef struct args
{
    OrderedList *task_list;
    Stack *modifications;
} args;

int compare_priority(void *a, void *b) {
    return ((Task*) a)->priority > ((Task*) b)->priority;
}

int compare_text(void *a, void *b) {
    return strcmp( ((Task*) a)->description, ((Task*) b)->description );
}

int compare_task(void *a, void *b) {
    return ((Task*) a)->priority != ((Task*) b)->priority || strcmp(((Task*) a)->description, ((Task*) b)->description);
}


void refresh(OrderedList *task_list) {
    char *string_to_print;
    unsigned string_size = 1;

    if(!ol_is_empty(task_list)) {
        OLIterator iter;
        ol_iter_init(&iter, task_list);
        unsigned item_index = 1; 

        Task aux_task;
        ol_get_current_item(&iter, &aux_task);
        char aux_str[115];
        sprintf(aux_str, "%u.  %s\n", item_index, aux_task.description);
        string_size += strlen(aux_str);
        string_to_print = malloc(string_size * sizeof(char));
        strcpy(string_to_print, aux_str);
        item_index++;

        for(; ol_iter_next(&iter); item_index++) {
            ol_get_current_item(&iter, &aux_task);
            sprintf(aux_str, "%u.  %s\n", item_index, aux_task.description);
            string_size += strlen(aux_str);
            string_to_print = realloc(string_to_print, string_size * sizeof(char));
            strcat(string_to_print, aux_str);
        }
    }
    else {
        string_to_print = malloc(string_size * sizeof(char));
        strcpy(string_to_print, "\0");
    }

    gtk_text_buffer_set_text(buffer, string_to_print, -1);

    free(string_to_print);    
}


void add_task(GtkWidget *calculate, gpointer *data) {
    args *arguments = (args*) data;

    Task task;
    strcpy(task.description, (char*) gtk_entry_get_text(GTK_ENTRY(add_input)));
    task.priority = gtk_combo_box_get_active(GTK_COMBO_BOX(priority_options));

    if(strlen(task.description) > 0) {
        ol_push(arguments->task_list, task);

        Modification modification;
        strcpy(modification.description, "inclusao");
        modification.description = ADDITION;
        modification.target = task;
        stack_push(arguments->modifications, modification);

        refresh(arguments->task_list);
    }
}


void remove_task(GtkWidget *calculate, gpointer *data) {
    args *arguments = (args*) data;

    Task task_to_remove;
    strcpy(task_to_remove.description, (char*) gtk_entry_get_text(GTK_ENTRY(remove_input)));

    OLIterator iter;
    ol_iter_init(&iter, arguments->task_list);
    if(ol_search(&iter, &compare_text, task_to_remove)) {
        Modification modification;
        modification.description = REMOVAL;
        ol_get_current_item(&iter, &modification.target);
        stack_push(arguments->modifications, modification);

        ol_pop_current_item(&iter, NULL);

        refresh(arguments->task_list);
    }
}


void undo(GtkWidget *calculate, gpointer *data) {
    args *arguments = (args*) data;

    if(!stack_is_empty(arguments->modifications)) {
        Modification mod_to_undo;
        stack_pop(arguments->modifications, &mod_to_undo);


        if(mod_to_undo.description == ADDITION) {
            OLIterator iter;
            ol_iter_init(&iter, arguments->task_list);
            ol_search(&iter, &compare_task, mod_to_undo.target);
            ol_pop_current_item(&iter, NULL);

            refresh(arguments->task_list);
        }
        else if(mod_to_undo.description == REMOVAL) {
            ol_push(arguments->task_list, mod_to_undo.target);
            refresh(arguments->task_list);
        }
    }
}


int main(int argc, char **argv) {
    gtk_init(&argc, &argv);

    OrderedList task_list;
    Stack modifications;
    ol_init(&task_list, &compare_priority);
    stack_init(&modifications);

    args arguments;
    arguments.task_list = &task_list;
    arguments.modifications = &modifications;

    // level 1
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Lista de tarefas");
    gtk_window_set_default_size(GTK_WINDOW(window), 630, 225);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // END level 1

    // level 2
    container = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_widget_set_size_request(container, 200, -1);
    gtk_container_add(GTK_CONTAINER(window), container);
    // END level 2

    // level 3
    display_frame = gtk_frame_new(NULL);
    gtk_paned_pack1(GTK_PANED(container), display_frame, TRUE, FALSE);
    gtk_frame_set_shadow_type(GTK_FRAME(display_frame), GTK_SHADOW_IN);
    gtk_widget_set_size_request(display_frame, 50, -1);

    controls_frame = gtk_frame_new(NULL);
    gtk_paned_pack2(GTK_PANED(container), controls_frame, FALSE, FALSE);
    gtk_frame_set_shadow_type(GTK_FRAME(controls_frame), GTK_SHADOW_IN);
    gtk_widget_set_size_request(controls_frame, 50, -1);
    // END level 3

    // level 4
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(display_frame), scrolled_window);

    button_box = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(controls_frame), button_box);
    //END level 4

    // level 5
    tasks = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tasks));
    gtk_text_view_set_editable(GTK_TEXT_VIEW(tasks), 0);
    gtk_container_add(GTK_CONTAINER(scrolled_window), tasks);

    priority_options = gtk_combo_box_text_new();
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(priority_options), NULL, "Baixa");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(priority_options), NULL, "Média");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(priority_options), NULL, "Alta");
    gtk_combo_box_set_active(GTK_COMBO_BOX(priority_options), 0);
    gtk_fixed_put(GTK_FIXED(button_box), priority_options, 280, 40);

    add_input = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(button_box), add_input, 100, 40);

    remove_input = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(button_box), remove_input, 100, 90);

    add_button = gtk_button_new_with_label("Adicionar tarefa");
    gtk_fixed_put(GTK_FIXED(button_box), add_button, 375, 40);
    g_signal_connect(add_button, "clicked", G_CALLBACK(add_task), &arguments);

    remove_button = gtk_button_new_with_label("Remover tarefa");
    gtk_fixed_put(GTK_FIXED(button_box), remove_button, 280, 90);
    g_signal_connect(remove_button, "clicked", G_CALLBACK(remove_task), &arguments);

    undo_button = gtk_button_new_with_label("Desfazer ação");
    gtk_fixed_put(GTK_FIXED(button_box), undo_button, 100, 140);
    g_signal_connect(undo_button, "clicked", G_CALLBACK(undo), &arguments);
    //END level 5

    gtk_widget_show_all(window);

    gtk_main();

    ol_destroy(&task_list);
    stack_destroy(&modifications);
}
