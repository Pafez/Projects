#include "linkedList.h"
#include <stdio.h>

int main() {
    struct LinkedList * test = LL_Init();
    LL_PushBack(test, 1);
    LL_PushBack(test, 3);
    LL_PushBack(test, 7);
    LL_PushFront(test, 0);
    LL_PushFront(test, -1);
    LL_PushAt(test, 5, 9);

    int i, k, l = test->length, fetch_fail;
    for (i=0;i<l;i++) {
        fetch_fail = LL_ValueAt(test, i, &k);
        if (!fetch_fail) printf("%d\n", k);
        else printf("Error: %d\n", fetch_fail);
    }
        
    LL_Delete(test);
    return 0;
}
