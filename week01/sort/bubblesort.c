#include <stdio.h>

#define SAMPLE_COUNT 10000
int sample[SAMPLE_COUNT];
int loop_count=0;

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

void sort(int data[], int count)
{
        int i, j;
        int n = count - 1;

        for (i = 0; i < n; i++) {
                for (j = 0; j < n - i; j++) {
			loop_count++;
                        if (data[j] > data[j + 1]) {
                                swap_array(data, j, j + 1);
			}
                }
        }
}

int main(void)
{
        read_data(sample,SAMPLE_COUNT);
        sort(sample, SAMPLE_COUNT);
	printf("%d" ,loop_count);
        return 0;
}
