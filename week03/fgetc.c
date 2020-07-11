#include <stdio.h>
#include <time.h>


int main(int argc, char *argv[])
{
    int c;
    FILE *fps, *fpd;
    clock_t start,end;

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

    while ((c = fgetc(fps)) != EOF) {
        fputc(c, fpd);
    }

    fclose(fpd);
    fclose(fps);

    end = clock();

    printf("%.5f\n", (double)(end-start)/CLOCKS_PER_SEC);

    return 0;
}
