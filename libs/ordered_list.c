//Guilherme Bortoletto
//Ryan Sakurai
//Vinicius Castro

#include "ordered_list.h"


void ol_init(OrderedList *list, int (*compare)(void *a, void *b)) {
    l->sentinela->ant = l->sentinela->prox = l->sentinela = (lo_node*) malloc(sizeof(lo_node));
    l->tamanho = 0;
    l->cmp = cmp;
}


void ol_destroy(OrderedList *list) {
    while(!lovazia(l))
        lopopi(l);
    
    free(l->sentinela);
}


void ol_push(OrderedList *list, T data) {
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


T ol_pop_first(OrderedList *list) {
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


T ol_pop_last(OrderedList *list) {
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


T ol_get_first(OrderedList *list) {
    if(!lovazia(l))
        return l->sentinela->prox->dado;
}


T ol_get_last(OrderedList *list) {
    if(!lovazia(l))
        return l->sentinela->ant->dado;
}


unsigned ol_get_size(OrderedList *list) {
    return l->tamanho;
}


bool ol_is_empty(OrderedList *list) {
    if(l->tamanho)
        return false;
    else
        return true;
}


void ol_iter_init(OLIterator *iter, OrderedList *list) {
    i->estrutura = l;
    i->elemento = l->sentinela->prox;
}


void ol_iter_next(OLIterator *iter) {
    i->elemento = i->elemento->prox;
}


bool ol_search(OLIterator *iter, int (*compare)(void *a, void *b), T data) {
    //procurando o elemento
    for(loiteradori(i->estrutura, i); !loacabou(i) && !(*cmp)(&dado, &i->elemento->dado); lomoverprox(i));

    if(loacabou(i)) //quer dizer que a lista acabou e o elemento não foi encontrado
        return false;
    else
        return true;
}


T ol_get_current(OLIterator *iter) {
    if(i->elemento != i->estrutura->sentinela)
        return i->elemento->dado;
}


T ol_pop_current(OLIterator *iter) {
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
