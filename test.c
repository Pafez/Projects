#include <stdio.h>

int main() {
    int s = 23980;
    int a = s/1000, b = s%1000;
    printf("%d %d", a, b);
    return 0;
}