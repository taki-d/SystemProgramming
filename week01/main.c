#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[8];

    for (int i = 0; i < sizeof(a)/sizeof(int); ++i) {
        a[i] = i;
    }

    for (int i = 0; i < sizeof(a)/sizeof(int); ++i) {
        printf("%d element is %d\n",i,a[i]);
    }

    return 0;
}
