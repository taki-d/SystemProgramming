#include <stdio.h>

#define DATA_COUNT 10000
int data[DATA_COUNT];
int count = 0;

void print_data(int a[], int count)
{
    int i;

    for (i = 0; i < count; i++) {
        printf("%2d ", a[i]);
    }
    printf("\n");
}

void swap_array(int a[], int i, int j)
{
    int tmp;

    tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void sort(int data[], int left, int right)
{
    int l = left,r = right;
    int pivot = data[(left+right)/2];

    while(1){
        while(data[l] < pivot) ++count,++l;
        while(data[r] > pivot) ++count,--r;

        if(l > r) break;

        // swap if smaller than pivot
        swap_array(data,l,r);
        ++l; --r;
    }

    if(left < r) sort(data,left,r);
    if(l < right) sort(data,l,right);
}


int main(void)
{
    srand(1);
    for(int i = 0; i < DATA_COUNT; ++i){
        data[i] = rand();
    }

    sort(data, 0, DATA_COUNT-1);
    printf("%d\n", count);
    return 0;
}
