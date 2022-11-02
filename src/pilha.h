//Guilherme Bortoletto
//Ryan Sakurai
//Vinicius Castro

#ifndef PILHA_H
#define PILHA_H

#include <stdlib.h>
#include <stdbool.h>
#include "macros.h"

typedef acao U;

typedef struct pilha
{
    U *vetor; //vetor da pilha
    int i_topo; //índice do topo
    unsigned t_vetor; //tamanho do vetor
} pilha;

void pinicializar(pilha *p);
// Parâmetros: ponteiro de pilha
// Função: inicializa a pilha
// Retorno: nenhum

void pdestruir(pilha *p);
// Parâmetros: ponteiro de pilha
// Função: destrói a pilha
// Retorno: nenhum

void ppush(pilha *p, U dado);
// Parâmetros: ponteiro de pilha e dado de tipo U
// Função: adiciona o dado no topo da pilha
// Retorno: nenhum

U ppop(pilha *p);
// Parâmetros: ponteiro de pilha
// Função: se a pilha não estiver vazia, retira o elemento do seu topo e o retorna
// Retorno: dado de tipo U

U ptopo(pilha *p);
// Parâmetros: ponteiro de pilha
// Função: se a pilha não estiver vazia, retorna o elemento do seu topo
// Retorno: dado de tipo U

unsigned ptamanho(pilha *p);
// Parâmetros: ponteiro de pilha
// Função: retorna o tamanho da pilha
// Retorno: unsigned int

bool pvazia(pilha *p);
// Parâmetros: ponteiro de pilha
// Função: retorna true/1 se a pilha estiver vazia e false/0 se não estiver
// Retorno: booleano

#endif