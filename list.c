#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* Lista = (List *) malloc(sizeof(List));
    if (Lista == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Lista->head = NULL;
    Lista->tail = NULL;
    Lista->current = NULL;
    return Lista;
}

void * firstList(List * list) {
    if (list->head != NULL)
    {
        list->current = list->head;
        return list->current->data;
    }
    return NULL;
}

void * nextList(List * list) {
    if (list->current != NULL && list->current->next)
    {
        list->current = list->current->next;
        return list->current->data;
    }
    return NULL;
}

void * lastList(List * list) {
    if (list->tail != NULL)
    {
        list->current = list->tail;
        return list->current->data;
    }
    return NULL;
}

void * prevList(List * list) {
    if (list->current == NULL || list->current->prev == NULL)
    {
        return NULL;
    }
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node* nodo = createNode(data);
    if (list->head != NULL)
    {
        nodo->next = list->head;
        list->head->prev = nodo;
        list->head = nodo;
    }
    else
    {
        list->head = nodo;
        list->tail = nodo;
    }

    list->current = nodo;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if (list->current == NULL)
    {
        return;
    }
    else
    {
        Node* nodo = createNode(data);
        nodo->next = list->current->next;
        nodo->prev = list->current;

        list->current->next = nodo;

        if (list->current->next != NULL)
        {
            list->current->next->prev = nodo;
        }

        list->current->next = nodo;

        if (list->current == list->tail)
        {
            list->tail = nodo;
        }
        list->current = nodo;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    Node* aux = list->current;
    void* dato_aux = aux->data;
    if (list->current == NULL)
    {
        return NULL;
    }

    if (aux->prev != NULL)
    {
        aux->prev->next = aux->next;
    }
    else
    {
        list->head = aux->next;
    }

    if (aux->next != NULL)
    {
        aux->next->prev = aux->prev;
    }
    else
    {
        list->tail = aux->prev;
    }

    list->current = aux->next;
    free(aux);
    return dato_aux;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}