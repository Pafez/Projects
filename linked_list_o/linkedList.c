#include "linkedList.h"
#include <stdlib.h>

static struct Node * List_Init(int headvalue) {
    struct Node *self = malloc(sizeof(struct Node));
    self->value = headvalue;
    self->next = NULL;
    return self;
}

struct LinkedList * LL_Init() {
    struct LinkedList * self = malloc(sizeof(struct LinkedList));
    self->pointer = NULL;
    self->length = 0;
    return self;
}

static int LL_ConditionalFirstElement(struct LinkedList * list, int value) {
    if (list->length == 0) {
        list->pointer = List_Init(value);
        return 0;
    }
    return 1;
}

static void List_Delete(struct Node *head) {
    if (head->next != NULL) {
        List_Delete(head->next);
    }
    free(head);
}

void LL_Delete(struct LinkedList * list) {
    if (list->length != 0) List_Delete(list->pointer);
    free(list);
}

int LL_Length(struct LinkedList * list) {
    return list->length;
}

static enum ErrorCode List_ValueAt(struct Node *head, int index, int * value) {
    int i = 0;
    struct Node *iterator = head;
    while (i < index) {
        iterator = iterator->next;
        i++;
    }
    *value =  iterator->value;
    return errOK;
}

enum ErrorCode LL_ValueAt(struct LinkedList * list, int index, int * value) {
    if (list->length == 0) return errEmptyList;
    if (index < 0) return errInvalidIndex;
    if (list->length <= index) return errIndexOutOfRange;
    return List_ValueAt(list->pointer, index, value);
}

static enum ErrorCode List_PushAt(struct Node * head, int index, int value) {
    int i = 0;
    struct Node *iterator = head;
    while (i < index) {
        iterator = iterator->next;
        i++;
    }
    struct Node * temp = List_Init(iterator->value);
    temp->next = iterator->next;
    
    iterator->value = value;
    iterator->next = temp;

    return errOK;
}

enum ErrorCode LL_PushAt(struct LinkedList * list, int index, int value) {
    enum ErrorCode is_error = errOK;
    if (list->length < index && index < 0) return errInvalidIndex;
    if (list->length == index) return LL_PushBack(list, value);
    if (LL_ConditionalFirstElement(list, value)) {
        is_error = List_PushAt(list->pointer, index, value);
    }
    list->length++;
    return is_error;
}

static enum ErrorCode List_PushFront(struct Node * head, int value) {
    return List_PushAt(head, 0, value);
}

enum ErrorCode LL_PushFront(struct LinkedList * list, int value) {
    enum ErrorCode is_error = errOK;
    if (LL_ConditionalFirstElement(list, value)) {
        is_error = List_PushFront(list->pointer, value);
    }
    list->length++;
    return is_error;
}

static enum ErrorCode List_PushBack(struct Node * head, int value) {
    struct Node *iterator = head;
    while (iterator->next != NULL) {
        iterator = iterator->next;
    }
    iterator->next = List_Init(value);
    return errOK;
}

enum ErrorCode LL_PushBack(struct LinkedList * list, int value) {
    enum ErrorCode is_error = errOK;
    if (LL_ConditionalFirstElement(list, value)) {
        is_error = List_PushBack(list->pointer, value);
    }
    list->length++;
    return is_error;
}

static enum ErrorCode List_PopAt(struct Node * head, int index, int * value) {
    struct Node * iterator = head;
    int Value = head->value;
    if (index == 0) {
        head->value = head->next->value;
        head->next = head->next->next;
        free(iterator->next);
        *value = Value;
    }
    int i = 0;
    while (i < index-1) {
        iterator = iterator->next;
        i++;
    }
    struct Node * temp = iterator->next;
    Value = iterator->next->value;
    iterator->next = iterator->next->next;
    free(temp);
    *value = Value;
    return errOK;
}

enum ErrorCode LL_PopAt(struct LinkedList * list, int index, int * value) {
    if (list->length == 0) return errEmptyList;
    if (index < 0) return errInvalidIndex;
    if (list->length <= index) return errIndexOutOfRange;
    list->length--;
    return List_PopAt(list->pointer, index, value);
}

static enum ErrorCode List_PopFront(struct Node * head, int * value) {
    return List_PopAt(head, 0, value);
}

enum ErrorCode LL_PopFront(struct LinkedList * list, int * value) {
    if (list->length == 0) return errEmptyList;
    list->length--;
    return List_PopFront(list->pointer, value);
}

static enum ErrorCode List_PopBack(struct Node * head, int * value) {
    struct Node * iterator = head;
    int i = 0;
    while (iterator->next->next != NULL) {
        iterator = iterator->next;
        i++;
    }
    struct Node * temp = iterator->next;
    int Value = iterator->next->value;
    iterator->next = NULL;
    free(temp);
    *value = Value;
    return errOK;
}

enum ErrorCode LL_PopBack(struct LinkedList * list, int * value) {
    if (list->length == 0) return errEmptyList;
    list->length--;
    return List_PopBack(list->pointer, value);
}

static int List_Contains(struct Node * head, int value) {
    int contains = 0;
    struct Node * iterator = head;
    while (iterator->next != NULL) {
        if (iterator->value == value) {
            contains = 1;
        }
        iterator = iterator->next;
    }
    return contains;
}

int LL_Contains(struct LinkedList * list, int value) {
    if (list->length == 0) {
        return 0;
    }
    return List_Contains(list->pointer, value);
}

static enum ErrorCode List_IndexOf(struct Node * head, int value) {
    int i = 0;
    struct Node * iterator = head;
    while (iterator->value != value) {
        iterator = iterator->next;
        i++;
    }
    if (iterator->value == value) {
        return i;
    }
    return errValueNotFound;
}

enum ErrorCode LL_IndexOf(struct LinkedList * list, int value) {
    return List_IndexOf(list->pointer, value);
}

static enum ErrorCode List_Remove(struct Node * head, int value) {
    int i = List_IndexOf(head, value);
    if (i == errValueNotFound) {
        return i;
    }
    int flush;
    List_PopAt(head, i, &flush);
    return errOK;
}

enum ErrorCode LL_Remove(struct LinkedList * list, int value) {
    if (list->length == 0) {
        return errEmptyList;
    }
    list->length--;
    return List_Remove(list->pointer, value);
}
