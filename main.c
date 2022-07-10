//Guilherme Bortoletto
//Ryan Sakurai
//Vinicius Castro

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h> //gtk3
#include "lista_ordenada.h"
#include "pilha.h"
#include "macros.h"

GtkWidget *window, *container, *frame1, *scrolled_window, *tarefas, *frame2, *caixa_botoes, *opt_prioridade, *input_add, *input_remov, *btn_add, *btn_remov, *btn_desfazer;
GtkTextBuffer *buffer;

typedef struct args
{
    lo_lista *lista;
    pilha *modificacoes;
} args;

int maior_prioridade(void *a, void *b)
{
    return ((atividade *)a)->prioridade > ((atividade *)b)->prioridade;
}

int igual_completo(void *a, void *b)
{
    return ((atividade *)a)->prioridade == ((atividade *)b)->prioridade && strcmp(((atividade *)a)->texto, ((atividade *)b)->texto) == 0;
}

int igual_texto(void *a, void *b)
{
    return strcmp(((atividade *)a)->texto, ((atividade *)b)->texto) == 0;
}

void refresh(lo_lista *lista)
{
    char aux[115]; //string auxiliar
    char *string_lista; //string que vai ser printada
    unsigned tamanho = 1; //toda string tem 1 espaço para o \0

    if(!lovazia(lista))
    {
        lo_iterador i; loiteradori(lista, &i);
        unsigned indice = 1; 

        //primeira iteração
        sprintf(aux, "%u.  %s\n", indice, loelemento(&i).texto);
        tamanho += strlen(aux);
        string_lista = (char*) malloc(tamanho*sizeof(char)); //string_lista segue o tamanho exato de caracteres
        strcpy(string_lista, aux);
        lomoverprox(&i);
        indice++;

        //resto das iterações
        for(; !loacabou(&i); lomoverprox(&i), indice++)
        {
            sprintf(aux, "%u.  %s\n", indice, loelemento(&i).texto);
            tamanho += strlen(aux);
            string_lista = (char*) realloc(string_lista, tamanho*sizeof(char));
            strcat(string_lista, aux);
        }
    }

    else
    {
        //se a lista estiver vazia, nada será printado
        string_lista = (char*) malloc(sizeof(char));
        strcpy(string_lista, "\0");
    }

    gtk_text_buffer_set_text(buffer, string_lista, -1);

    free(string_lista);    
}

void incluir_atividade(GtkWidget *calculate, gpointer *data)
{
    args *argumentos = (args*) data;

    //declarando e inicializando tarefa
    atividade tarefa;
    sprintf(tarefa.texto, "%s", gtk_entry_get_text(GTK_ENTRY(input_add)));
    tarefa.prioridade = gtk_combo_box_get_active(GTK_COMBO_BOX(opt_prioridade));

    if(strlen(tarefa.texto)>0)
    {
        //adicionando tarefa na lista
        lopush(argumentos->lista, tarefa);

        //adicionando acao na pilha
        acao acao;
        strcpy(acao.texto, "inclusao");
        acao.atividade = tarefa;
        ppush(argumentos->modificacoes, acao);

        refresh(argumentos->lista);
    }
}

void remover_atividade(GtkWidget *calculate, gpointer *data)
{
    args *argumentos = (args*) data;

    atividade tarefa_remover;
    strcpy(tarefa_remover.texto, (char*) gtk_entry_get_text(GTK_ENTRY(input_remov)));

    lo_iterador i; loiteradori(argumentos->lista, &i);    
    if(loprocurar(&i, tarefa_remover, &igual_texto))
    {
        //adicionando acao na pilha
        acao acao;
        strcpy(acao.texto, "remocao");
        acao.atividade = loelemento(&i);
        ppush(argumentos->modificacoes, acao);

        //tirando tarefa da lista
        lopopelemento(&i);

        refresh(argumentos->lista);
    }
}

void desfazer(GtkWidget *calculate, gpointer *data)
{
    args *argumentos = (args*) data;

    if(!pvazia(argumentos->modificacoes))
    {
        acao acao_reverter = ppop(argumentos->modificacoes);

        if(strcmp(acao_reverter.texto, "inclusao") == 0)
        {
            lo_iterador i; loiteradori(argumentos->lista, &i);
            loprocurar(&i, acao_reverter.atividade, &igual_completo);
            lopopelemento(&i);

            refresh(argumentos->lista);
        }

        else if(strcmp(acao_reverter.texto, "remocao") == 0)
        {
            lopush(argumentos->lista, acao_reverter.atividade);

            refresh(argumentos->lista);
        }
    }
}

/* 
Hierarquia dos widgets:
    window
        container
            frame1
                scrolled_window
                    tarefas
            frame2
                caixa_botoes
                    opt_prioridade
                    input_add
                    input_remov
                    btn_add
                    btn_remov
                    btn_desfazer
*/

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    //lista de tarefas ordenada por: prioridade -> ordem de chegada
    lo_lista lista; loinicializar(&lista, &maior_prioridade);

    //pilha de modificações feitas na lista
    pilha modificacoes; pinicializar(&modificacoes); 

    //argumentos que serão passados quando um botão for ativado
    args argumentos;
    argumentos.lista = &lista;
    argumentos.modificacoes = &modificacoes;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Lista de tarefas");
    gtk_window_set_default_size(GTK_WINDOW(window), 630, 225);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    container = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_widget_set_size_request(container, 200, -1);
    gtk_container_add(GTK_CONTAINER(window), container);

    frame1 = gtk_frame_new(NULL);
    gtk_paned_pack1(GTK_PANED(container), frame1, TRUE, FALSE);
    gtk_frame_set_shadow_type(GTK_FRAME(frame1), GTK_SHADOW_IN);
    gtk_widget_set_size_request(frame1, 50, -1);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(frame1), scrolled_window);

    tarefas = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tarefas));
    gtk_text_view_set_editable(GTK_TEXT_VIEW(tarefas), 0);
    gtk_container_add(GTK_CONTAINER(scrolled_window), tarefas);

    frame2 = gtk_frame_new(NULL);
    gtk_paned_pack2(GTK_PANED(container), frame2, FALSE, FALSE);
    gtk_frame_set_shadow_type(GTK_FRAME(frame2), GTK_SHADOW_IN);
    gtk_widget_set_size_request(frame2, 50, -1);

    caixa_botoes = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(frame2), caixa_botoes);

    opt_prioridade = gtk_combo_box_text_new();
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(opt_prioridade), NULL, "Baixa");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(opt_prioridade), NULL, "Média");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(opt_prioridade), NULL, "Alta");
    gtk_combo_box_set_active(GTK_COMBO_BOX(opt_prioridade), 0);
    gtk_fixed_put(GTK_FIXED(caixa_botoes), opt_prioridade, 280, 40);

    input_add = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(caixa_botoes), input_add, 100, 40);

    input_remov = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(caixa_botoes), input_remov, 100, 90);

    btn_add = gtk_button_new_with_label("Adicionar tarefa");
    gtk_fixed_put(GTK_FIXED(caixa_botoes), btn_add, 375, 40);
    g_signal_connect(btn_add, "clicked", G_CALLBACK(incluir_atividade), &argumentos);

    btn_remov = gtk_button_new_with_label("Remover tarefa");
    gtk_fixed_put(GTK_FIXED(caixa_botoes), btn_remov, 280, 90);
    g_signal_connect(btn_remov, "clicked", G_CALLBACK(remover_atividade), &argumentos);

    btn_desfazer = gtk_button_new_with_label("Desfazer ação");
    gtk_fixed_put(GTK_FIXED(caixa_botoes), btn_desfazer, 100, 140);
    g_signal_connect(btn_desfazer, "clicked", G_CALLBACK(desfazer), &argumentos);

    gtk_widget_show_all(window);

    gtk_main();

    lodestruir(&lista);
    pdestruir(&modificacoes);
}