#ifndef LINKED_LIST_5246542
#define LINKED_LIST_5246542

enum ErrorCode {
    errOK,
    errEmptyList,
    errInvalidIndex,
    errIndexOutOfRange,
    errValueNotFound,
    errInvalidType
};

struct Node {
    int value;
    struct Node *next;
};

struct LinkedList {
    struct Node * pointer;
    int length;
};

struct LinkedList * LL_Init();
void LL_Delete(struct LinkedList * list);
int LL_Length(struct LinkedList * list);
enum ErrorCode LL_ValueAt(struct LinkedList * list, int index, int * value);
enum ErrorCode LL_PushAt(struct LinkedList * list, int index, int value);
enum ErrorCode LL_PushFront(struct LinkedList * list, int value);
enum ErrorCode LL_PushBack(struct LinkedList * list, int value);
enum ErrorCode LL_PopAt(struct LinkedList * list, int index, int * value);
enum ErrorCode LL_PopFront(struct LinkedList * list, int * value);
enum ErrorCode LL_PopBack(struct LinkedList * list, int * value);
int LL_Contains(struct LinkedList * list, int value);
enum ErrorCode LL_IndexOf(struct LinkedList * list, int value);
enum ErrorCode LL_Remove(struct LinkedList * list, int value);

#endif //endif for LINKED_LIST_5246542
