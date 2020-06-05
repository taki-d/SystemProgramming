#include <stdio.h>
#include <time.h>


int main(int argc, char *argv[])
{
    int c;
    FILE *fps, *fpd;
    clock_t start,end;
    char *buf;


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

    while(fgets(buf, buf_size, fps) != NULL){
        fputs(buf, fpd);
    }

    fclose(fpd);
    fclose(fps);

    end = clock();

    printf("%.5f", (double)(end-start)/CLOCKS_PER_SEC);

    return 0;
}
