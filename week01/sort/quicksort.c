#include <stdio.h>

#define SAMPLE_COUNT 10000
int sample[SAMPLE_COUNT];

void read_data(int a[], int count){
    FILE *f;
    f = fopen("random","r");

    if(f == NULL){
        printf("file open failed");
    }

    for (int i = 0; i < (count/4); ++i) {
        fscanf(f, "%d %d %d %d\n", &(a[i*4]), &(a[i*4+1]), &(a[i*4+2]), &(a[i*4+3]));
    }

    fclose(f);
}

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
        while(data[l] < pivot) ++l;
        while(data[r] > pivot) --r;

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
        read_data(sample,SAMPLE_COUNT);
        print_data(sample,SAMPLE_COUNT);
        sort(sample, 0, SAMPLE_COUNT-1);
        print_data(sample, SAMPLE_COUNT);
        return 0;
}
