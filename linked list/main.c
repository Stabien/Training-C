#include <stdio.h>
#include <stdlib.h>
#include "./list.h"

List *initialize()
{
    List *list = malloc(sizeof(*list));

    if (!list) exit(EXIT_FAILURE);

    list->first = NULL;
    list->last = NULL;

    return list;
}

void pushFront(List *list, int nb)
{
    Element *new = malloc(sizeof(*new));

    if (!new) exit(EXIT_FAILURE);

    new->nb = nb;
    new->next = list->first;
    new->previous = NULL;

    if (list->first)
        list->first->previous = new;
    else {
        list->last = new;
        list->last->next = NULL;
    }

    list->first = new;
}

void pushBack(List *list, int nb)
{
    Element *new = malloc(sizeof(*new));

    if (!new) exit(EXIT_FAILURE);

    new->nb = nb;
    new->previous = list->last;
    new->next = NULL;

    if (list->last)
        list->last->next = new;
    else {
        list->first = new;
        list->first->previous = NULL;
    }

    list->last = new;
}

int getListLength(List *list)
{
    Element *current = list->first;
    int i = 0;

    while (current) {
        current = current->next;
        i++;
    }
    return i;
}

Element *getElementByPosition(List *list, int pos)
{
    Element *current = list->first;
    int listLength = getListLength(list);

    if (listLength < pos) {
        printf("Index out of range");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < pos; i++)
        current = current->next;

    return current;
}

void insertAfterElement(List *list, int pos, int nb)
{
    Element *current = getElementByPosition(list, pos);
    Element *new = malloc(sizeof(*new));

    if (!new) exit(EXIT_FAILURE);

    new->nb = nb;
    new->previous = current;

    if (!current) {
        new->next = NULL;
        list->first = new;
        list->last = new;
    }
    else {
        if (!current->next) {
            new->next = NULL;
            current->next = new;
            list->last = new;
        }
        else {
            new->next = current->next;
            current->next->previous = new;
            current->next = new;
        }
    }
}

void insertBeforeElement(List *list, int pos, int nb)
{
    Element *current = getElementByPosition(list, pos);
    Element *new = malloc(sizeof(*new));

    if (!new) exit(EXIT_FAILURE);

    new->nb = nb;
    new->next = current;

    if (!current) {
        new->previous = NULL;
        list->first = new;
        list->last = new;
    }
    else {
        if (!current->previous) {
            new->previous = NULL;
            current->previous = new;
            list->first = new;
        }
        else {
            new->previous = current->previous;
            current->previous->next = new;
            current->previous = new;
        }
    }
}

void popFront(List *list)
{
    if (list->first) {
        list->first = list->first->next;
        list->first->previous = NULL;
    }
    else
        list->last = NULL;
}

void popBack(List* list)
{
    if (list->last) {
        list->last = list->last->previous;
        list->last->next = NULL;
    }
    else
        list->first = NULL;
}


void displayList(List *list)
{
    Element *current = list->first;

    while(current) {
        printf("%d\n", current->nb);
        current = current->next;
    }
    free(current);
}

int main(int argc, char *argv[])
{
    List *list = initialize();

    insertAfterElement(list, 0, 5);
    insertBeforeElement(list, 1, 15);
    insertBeforeElement(list, 2, 25);
    displayList(list);

    return 0;
}
