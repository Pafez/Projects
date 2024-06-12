#ifndef LINKED_LIST_5246542
#define LINKED_LIST_5246542

struct Node {
    int value;
    struct Node *next;
};

struct Node *List_Init(int headvalue);
void List_Delete(struct Node *self);

struct Node *List_Append(struct Node *head, int value);
struct Node *List_AppInit(int headvalue, struct Node *tail);
int List_GetValue(struct Node *head, int index);
struct Node *List_UpdateValue(struct Node *head, int index, int value);

#endif
