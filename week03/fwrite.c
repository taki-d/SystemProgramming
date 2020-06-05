#include <stdio.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int c;
    FILE *fps, *fpd;
    clock_t start,end;

    size_t buf_size = atoi(argv[3]);
    char *buf = malloc(buf_size);

    start = clock();

    fps = fopen(argv[1], "r");
    if (fps == NULL) {
        perror(argv[1]);
        exit(1);
    }

    fpd = fopen(argv[2], "w");
    if (fpd == NULL) {
        perror(argv[2]);
        fclose(fps);
        exit(1);
    }

    int size;
    while((size = fread(buf, sizeof(char), buf_size, fps)) != 0){
          fwrite(buf, sizeof(char), size, fpd);
    }

    fclose(fpd);
    fclose(fps);

    end = clock();

    printf("%.5f\n", (double)(end-start)/CLOCKS_PER_SEC);

    return 0;
}
