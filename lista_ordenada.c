//Guilherme Bortoletto
//Ryan Sakurai
//Vinicius Castro

#include "lista_ordenada.h"

void loinicializar(lo_lista *l, int (*cmp)(void *a, void *b))
{
    l->sentinela->ant = l->sentinela->prox = l->sentinela = (lo_node*) malloc(sizeof(lo_node));
    l->tamanho = 0;
    l->cmp = cmp;
}

void lodestruir(lo_lista *l)
{
    while(!lovazia(l))
        lopopi(l);
    
    free(l->sentinela);
}

void lopush(lo_lista *l, T dado)
{
    lo_node *novo = (lo_node*) malloc(sizeof(lo_node));
    novo->dado = dado;

    //achando o elemento da lista que vai vir exatamente antes do node novo
    lo_iterador i;
    for(i.elemento = l->sentinela->ant; i.elemento != l->sentinela && (*l->cmp)(&novo->dado, &i.elemento->dado); lomoverant(&i));

    //inserindo node novo entre o elemento e o próximo
    novo->ant = i.elemento;
    novo->prox = i.elemento->prox;
    novo->prox->ant = novo;
    novo->ant->prox = novo;

    l->tamanho++;
}

T lopopi(lo_lista *l)
{
    if(!lovazia(l))
    {
        lo_node *removido = l->sentinela->prox;
        T retorno = removido->dado;

        //arrumando os links da lista
        l->sentinela->prox = removido->prox;
        l->sentinela->prox->ant = l->sentinela;

        free(removido);

        l->tamanho--;

        return retorno;
    }
}

T lopopf(lo_lista *l)
{
    if(!lovazia(l))
    {
        lo_node *removido = l->sentinela->ant;
        T retorno = removido->dado;

        //arrumando os links da lista
        l->sentinela->ant = removido->ant;
        l->sentinela->ant->prox = l->sentinela;

        free(removido);

        l->tamanho--;

        return retorno;
    }
}

T loprimeiro(lo_lista *l)
{
    if(!lovazia(l))
        return l->sentinela->prox->dado;
}

T loultimo(lo_lista *l)
{
    if(!lovazia(l))
        return l->sentinela->ant->dado;
}

unsigned lotamanho(lo_lista *l)
{
    return l->tamanho;
}

bool lovazia(lo_lista *l)
{
    if(l->tamanho)
        return false;
    else
        return true;
}

void loiteradori(lo_lista *l, lo_iterador *i)
{
    i->estrutura = l;
    i->elemento = l->sentinela->prox;
}

void loiteradorf(lo_lista *l, lo_iterador *i)
{
    i->estrutura = l;
    i->elemento = l->sentinela->ant;
}

void lomoverant(lo_iterador *i)
{
    i->elemento = i->elemento->ant;
}

void lomoverprox(lo_iterador *i)
{
    i->elemento = i->elemento->prox;
}

bool loacabou(lo_iterador *i)
{
    if(i->elemento == i->estrutura->sentinela)
        return true;
    else
        return false;
}

bool loprocurar(lo_iterador *i, T dado, int (*cmp)(void *a, void *b))
{
    //procurando o elemento
    for(loiteradori(i->estrutura, i); !loacabou(i) && !(*cmp)(&dado, &i->elemento->dado); lomoverprox(i));

    if(loacabou(i)) //quer dizer que a lista acabou e o elemento não foi encontrado
        return false;
    else
        return true;
}

T loelemento(lo_iterador *i)
{
    if(i->elemento != i->estrutura->sentinela)
        return i->elemento->dado;
}

T lopopelemento(lo_iterador *i)
{
    if(i->elemento != i->estrutura->sentinela)
    {
        lo_node *removido = i->elemento;
        T retorno = removido->dado;

        //removendo links da lista ao elemento
        removido->ant->prox = removido->prox;
        removido->prox->ant = removido->ant;
        
        //passando iterador para o proximo
        i->elemento = i->elemento->prox;

        free(removido);

        i->estrutura->tamanho--;

        return retorno;
    }
}