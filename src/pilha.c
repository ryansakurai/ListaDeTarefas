//Guilherme Bortoletto
//Ryan Sakurai
//Vinicius Castro

#include "pilha.h"

/* O i_topo de uma pilha é o índice do elemento que está no
   topo. Quando a pilha está vazia, i_topo == -1 */

void pinicializar(pilha *p)
{
    p->t_vetor = 1;
    p->vetor = (U*) malloc(sizeof(U));
    p->i_topo = -1;
}

void pdestruir(pilha *p)
{
    free(p->vetor);
}

void ppush(pilha *p, U dado)
{
    //se o vetor estiver cheio, ele dobra de tamanho
    if(ptamanho(p) == p->t_vetor)
    {
        p->vetor = (U*) realloc(p->vetor, (p->t_vetor*2) * sizeof(U));
        p->t_vetor *= 2;
    }

    p->i_topo++;
    p->vetor[p->i_topo] = dado;
}

U ppop(pilha *p)
{
    if(!pvazia(p))
    {
        U retorno = p->vetor[p->i_topo];

        p->i_topo--;

        /* se o tamanho da pilha for 1/4 do tamanho do vetor ou menos,
           o vetor é divido ao meio */
        if(p->t_vetor>1 && ptamanho(p) <= p->t_vetor/4)
        {
            p->vetor = (U*) realloc(p->vetor, (p->t_vetor/2) * sizeof(U));
            p->t_vetor /= 2;
        }
        //t_vetor==1 é excluido pois, nesse caso, o vetor já é minimo

        return retorno;
    }    
}

U ptopo(pilha *p)
{
    if(!pvazia(p))
        return p->vetor[p->i_topo];
}

unsigned ptamanho(pilha *p)
{
    return p->i_topo + 1;
}

bool pvazia(pilha *p)
{
    if(ptamanho(p))
        return false;
    else
        return true;
}