//Guilherme Bortoletto
//Ryan Sakurai
//Vinicius Castro

#ifndef LISTA_ORDENADA_H
#define LISTA_ORDENADA_H

#include <stdlib.h>
#include <stdbool.h>
#include "macros.h"

typedef atividade T;

typedef struct lo_node
{
    T dado; //conteúdo do node
    struct lo_node *ant, *prox; //node anterior e próximo node
} lo_node;

typedef struct lo_lista
{
    lo_node *sentinela; //sentinela
    unsigned tamanho; //tamanho da lista
    int (*cmp)(void *a, void *b); //função de comparação para ordenação
} lo_lista;

typedef struct lo_iterador
{
    lo_lista *estrutura; //lista
    lo_node *elemento; //elemento que o iterador aponta
} lo_iterador;

void loinicializar(lo_lista *l, int (*cmp)(void *a, void *b));
/* Parâmetros: ponteiro de lista e ponteiro da função que será usada na ordenação da lista
               (retorna true/1 se *a deve ser movido em direção ao início da lista
               e false/0 se ele não deve)
   Função: inicializa a lista
   Retorno: nenhum */

void lodestruir(lo_lista *l);
/* Parâmetros: ponteiro de lista
   Função: destrói a lista
   Retorno: nenhum */

void lopush(lo_lista *l, T dado);
/* Parâmetros: ponteiro de iterador, dado de tipo T
   Função: o elemento é inserido na lista, seguindo a ordenação definida na função
           loinicializar
   Retorno: nenhum */

T lopopi(lo_lista *l);
/* Parâmetros: ponteiro de lista
   Função: se a lista não estiver vazia, retira um elemento do seu início e o retorna
   Retorno: dado de tipo T */

T lopopf(lo_lista *l);
/* Parâmetros: ponteiro de lista
   Função: se a lista não estiver vazia, retira um elemento do seu fim e o retorna
   Retorno: dado de tipo T */

T loprimeiro(lo_lista *l);
/* Parâmetros: ponteiro de lista
   Função: se a lista não estiver vazia, retorna o seu primeiro elemento
   Retorno: dado de tipo T */

T loultimo(lo_lista *l);
/* Parâmetros: ponteiro de lista
   Função: se a lista não estiver vazia, retorna o seu último elemento
   Retorno: dado de tipo T */

unsigned lotamanho(lo_lista *l);
/* Parâmetros: ponteiro de lista
   Função: retorna o tamanho da lista
   Retorno: unsigned int */

bool lovazia(lo_lista *l);
/* Parâmetros: ponteiro de lista
   Função: retorna true/1 se a lista estiver vazia e false/0 se não estiver
   Retorno: booleano */

void loiteradori(lo_lista *l, lo_iterador *i);
/* Parâmetros: ponteiro de lista e ponteiro de iterador
   Função: o iterador aponta para o primeiro elemento da lista
           se a lista estiver vazia, o iterador aponta para um elemento fora da lista
           (neste caso, quando um elemento for adicionado, utilize um "lmoverant" ou
           "lmoverprox" para mover o iterador para ele)
   Retorno: nenhum */

void loiteradorf(lo_lista *l, lo_iterador *i);
/* Parâmetros: ponteiro de lista e ponteiro de iterador
   Função: o iterador aponta para o ultimo elemento da lista
           se a lista estiver vazia, o iterador aponta para um elemento fora da lista
           (neste caso, quando um elemento for adicionado, utilize um "lmoverant" ou
           "lmoverprox" para mover o iterador para ele)
   Retorno: nenhum */


void lomoverant(lo_iterador *i);
/* Parâmetros: ponteiro de iterador
   Função: o iterador é movido para o elemento anterior
   Retorno: nenhum */

void lomoverprox(lo_iterador *i);
/* Parâmetros: ponteiro de iterador
   Função: o iterador é movido para o proximo elemento
   Retorno: nenhum */

bool loacabou(lo_iterador *i);
/* Parâmetros: ponteiro de iterador
   Função: se o iterador estiver apontando para um elemento da lista, retorna false/0;
           se o iterador estiver apontando para um elemento fora da lista, retorna true/1;
   Retorno: booleano */

bool loprocurar(lo_iterador *i, T dado, int (*cmp)(void *a, void *b));
/* Parâmetros: ponteiro de iterador, dado a ser procurado e função que retorna true/1 se os parâmetros
               forem iguais e false/0 se não forem
   Função: o dado será procurado na lista: se for encontrado, o iterador vai apontá-lo e vai ser retornado
           true/1; se não for encontrado o iterador vai apontar um elemento fora da lista e vai ser retornado
           false/0 (se o dado estiver repetido, o encontrado será o primeiro que aparece na lista)
   Retorno: dado de tipo T */

T loelemento(lo_iterador *i);
/* Parâmetros: ponteiro de iterador
   Função: se o iterador apontar para um elemento da lista, retorna o elemento
   Retorno: tipo T */

T lopopelemento(lo_iterador *i);
/* Parâmetros: ponteiro de iterador
   Função: se o iterador apontar um elemento da lista, remove o elemento, o retorna e move o
           iterador para o elemento seguinte
   Retorno: tipo T */

#endif