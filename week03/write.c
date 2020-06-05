#include <stdio.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    clock_t start,end;

    size_t buf_size = atoi(argv[3]);
    char *buf = malloc(buf_size);

    int fps, fpd;
    int count;

    fps = open(argv[1], O_RDONLY);
    if (fps < 0) {
        perror("open: src");
        exit(1);
    }

    fpd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fpd < 0) {
        perror("open: dst");
        close(fps);
        exit(1);
    }

    while ((count = read(fps, buf, buf_size)) > 0) {
        if (write(fpd, buf, count) < 0) {
            perror("write");
            close(fpd);
            close(fps);
            exit(1);
        }
    }

    if (count < 0) {
        perror("read");
        close(fpd);
        close(fps);
        exit(1);
    }

    close(fpd);
    close(fps);

    end = clock();

    printf("%.5f\n", (double)(end-start)/CLOCKS_PER_SEC);

    return 0;
}
