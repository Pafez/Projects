#include "linkedlist.h"
#include <stdio.h>

int main() {
    struct Node *test_list = List_Init(1);
    int i;
    for (i=2;i<=5;i++)
        List_Append(test_list, i);
    int j, val;
    for (j=4;j>=0;j--) {
        val = List_GetValue(test_list, j);
        printf("%d", val);
    }
    printf("done");
}