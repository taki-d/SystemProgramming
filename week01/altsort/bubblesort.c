#include <stdio.h>

#define DATA_COUNT 10000
int data[DATA_COUNT];
int loop_count = 0;

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

void sort(int data[], int count){
    int i, j;
    int n = count - 1;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i; j++) {
            ++loop_count;
            if (data[j] > data[j + 1]) {
                swap_array(data, j, j + 1);
            }
        }
    }
}

int main(void)
{
    srand(1);
    for(int i = 0; i < DATA_COUNT; ++i){
        data[i] = rand();
    }

    sort(data, DATA_COUNT);
    printf("%d\n", loop_count);
    return 0;
}
