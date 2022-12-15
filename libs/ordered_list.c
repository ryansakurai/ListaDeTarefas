//Guilherme Bortoletto
//Ryan Sakurai
//Vinicius Castro

#include "ordered_list.h"


void ol_init(OrderedList *list, int (*compare)(void *a, void *b)) {
    list->sentinel->prev = list->sentinel->next = list->sentinel = malloc(sizeof(OLNode));
    list->size = 0;
    list->compare = compare;
}


void ol_destroy(OrderedList *list) {
    while(!ol_is_empty(list))
        ol_pop_first(list, NULL);
    
    free(list->sentinel);
    list->sentinel = NULL;
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


bool ol_pop_first(OrderedList *list, T *output) {
    if(!ol_is_empty(list)) {
        OLNode *popped = list->sentinel->next;
        if(output)
            *output = popped->data;

        list->sentinel->next = popped->next;
        list->sentinel->next->prev = list->sentinel;
        free(popped);
        list->size--;

        return true;
    }
    else {
        return false;
    }
}


bool ol_pop_last(OrderedList *list, T *output) {
    if(!ol_is_empty(list)) {
        OLNode *popped = list->sentinel->prev;
        if(output)
            *output = popped->data;

        list->sentinel->prev = popped->prev;
        list->sentinel->prev->next = list->sentinel;
        free(popped);
        list->size--;

        return true;
    }
    else {
        return false;
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
    if(list->size > 0)
        return false;
    else
        return true;
}


bool ol_iter_init(OLIterator *iter, OrderedList *list) {
    if(!ol_is_empty(list)) {
        iter->list = list;
        iter->current = list->sentinel->next;
        return true;
    }
    else {
        return false;
    }
}


bool ol_iter_next(OLIterator *iter) {
    if(iter->current->next != iter->list->sentinel) {
        iter->current = iter->current->next;
        return true;
    }
    else {
        return false;
    }
}


T ol_get_current(OLIterator *iter) {
    return iter->current->data;
}


T ol_pop_current(OLIterator *iter) {
    OLNode *popped = iter->current;
    T return_value = popped->data;

    popped->prev->next = popped->next;
    popped->next->prev = popped->prev;
    iter->current = iter->current->next;
    free(popped);
    iter->list->size--;

    return return_value;
}


bool ol_search(OLIterator *iter, int (*compare)(void *a, void *b), T data) {
    //procurando o elemento
    for(loiteradori(i->estrutura, i); !loacabou(i) && !(*cmp)(&dado, &i->elemento->dado); lomoverprox(i));

    if(loacabou(i)) //quer dizer que a lista acabou e o elemento não foi encontrado
        return false;
    else
        return true;
}
