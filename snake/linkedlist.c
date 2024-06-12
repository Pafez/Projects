#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>

struct Node *List_Init(int headvalue) {
    struct Node *self = malloc(sizeof(struct Node));
    self->value = headvalue;
    self->next = NULL;
    return self;
}

void List_Delete(struct Node *head) {
    if (head->next != NULL) {
        List_Delete(head->next);
    }
    free(head);
}

struct Node *List_Append(struct Node *head, int value) {
    struct Node *iterator = head;

    while (iterator->next != NULL) {
        iterator = iterator->next;
    }

    iterator->next = List_Init(value);
}

struct Node *List_AppInit(int headvalue, struct Node *tail) {
    struct Node *self = malloc(sizeof(struct Node));
    self->value = headvalue;
    self->next = tail;
    tail = self;
    return self;
}

int List_GetValue(struct Node *head, int index) {
    int i = 0;
    struct Node *iterator = head;
    while (i < index) {
        iterator = iterator->next;
        i++;
    }
    return iterator->value;
}

struct Node *List_UpdateValue(struct Node *head, int index, int value) {
    int i = 0;
    struct Node *iterator = head;
    while (i < index) {
        iterator = iterator->next;
        i++;
    }
    iterator->value = value;
}

