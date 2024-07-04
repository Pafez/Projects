#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node *next;
};

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

int List_Append(struct Node *head, int value) {
    struct Node *iterator = head;

    while (iterator->next != NULL) {
        iterator = iterator->next;
    }

    iterator->next = List_Init(value);
    return 0;
}

int List_Length(struct Node * head) {
    int i = 1;
    struct Node *iterator = head;
    while (iterator->next != NULL) {
        iterator = iterator->next;
        i++;
    }
    return i;
}

int List_ValueAt(struct Node *head, int index) {
    int i = 0;
    struct Node *iterator = head;
    while (i < index) {
        iterator = iterator->next;
        i++;
    }
    return iterator->value;
}

int List_PushAt(struct Node * head, int index, int value) {
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

    return 0;
}

int List_PushFront(struct Node * head, int value) {
    return List_PushAt(head, 0, value);
}

int List_PushBack(struct Node * head, int value) {
    struct Node *iterator = head;
    while (iterator->next != NULL) {
        iterator = iterator->next;
    }
    iterator->next = List_Init(value);
    return 0;
}

int List_PopAt(struct Node * head, int index) {
    struct Node * iterator = head;
    int value = head->value;
    if (index == 0) {
        head->value = head->next->value;
        head->next = head->next->next;
        free(iterator);
        return value;
    }
    int i = 0;
    while (i < index-1) {
        iterator = iterator->next;
        i++;
    }
    value = iterator->next->value;
    iterator->next = iterator->next->next;
    return value;
}

int List_PopFront(struct Node * head) {
    return List_PopAt(head, 0);
}

int List_PopBack(struct Node * head) {
    struct Node * iterator = head;
    int i = 0;
    while (iterator->next->next != NULL) {
        iterator = iterator->next;
        i++;
    }
    int value = iterator->next->value;
    iterator->next = NULL;
    return value;
}

int List_Contains(struct Node * head, int value) {
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

int main() {
    struct Node * test = List_Init(1);

    List_Append(test, 10);
    List_Append(test, 100);

    List_PushAt(test, 1, 3);
    List_PushFront(test, 0);
    List_PushBack(test, 1000);

    List_PopAt(test, 0);

    int i;
    for (i=0;i<List_Length(test);i++) {
        printf("%d\n", List_ValueAt(test, i));
    }
    List_Delete(test);
    return 0;
}


/*
1) push_back, push_front
2) length, value_at(5)
3) pop_back, pop_front
4) push_at(2, 20), pop_at(5)
5) contains(value), remove(value), index_of(value)
*/