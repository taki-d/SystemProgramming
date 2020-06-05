#include <stdio.h>

#define DATA_COUNT 6
int data[DATA_COUNT] = {8, 12, 3, 15, 7, 4};

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
        while(data[l] < pivot) printf("\t[%d]=%d < [pivot]=%d \n", l,data[l], pivot),++l;
        while(data[r] > pivot) printf("\t[%d]=%d > [pivot]=%d \n", r,data[r], pivot),--r;

        if(l > r) break;

        // swap if smaller than pivot
        printf(" ... swap!!");
        swap_array(data,l,r);
        printf("\n");
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
    print_data(data, DATA_COUNT);
    return 0;
}
