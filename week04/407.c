#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int p2c_fdc[2];
int c2p_fdc[2];
int flag = 1;

void do_parent(int max){
    close(c2p_fdc[1]);
    close(p2c_fdc[0]);

    for(int i = 1; i < max; i += 2){
        if(read(c2p_fdc[0], &flag, 1) < 0){
            perror("read");
        }

        printf("%c", (i/2) % 26 + 'a');
        fflush(stdout);

        if(write(p2c_fdc[1], &flag, 1) < 0){
            perror("write");
        }
    }

    close(c2p_fdc[0]);
    close(p2c_fdc[1]);
}

void do_child(int max){
    close(p2c_fdc[1]);
    close(c2p_fdc[0]);

    printf("0");
    fflush(stdout);
    if(write(c2p_fdc[1], &flag, 1) < 0) {
        perror("write");
    }

    if(max == 1) {
        exit(2);
    }

    for(int i = 2; i < max; i += 2){
        if(read(p2c_fdc[0], &flag, 1) < 0){
            perror("read");
        }

        printf("%d", (i/2) % 10);
        fflush(stdout);

        if(write(c2p_fdc[1], &flag, 1) < 0){
            perror("write");
        }
    }

    close(p2c_fdc[0]);
    close(c2p_fdc[1]);
}

int main(int argc, char* argv[]) {
    int max, pid, status;

    if(argc < 2) {
        printf("too few argments\n");
        exit(1);
    }

    max = atoi(argv[1]);
//    max = 60;

    if(pipe(p2c_fdc) < 0) {
        perror("pipe");
    }

    if(pipe(c2p_fdc) < 0) {
        perror("pipe");
    }

    if ((pid = fork()) < 0) {
        perror("fork");
    }

    if (pid == 0) {
        do_child(max);
    } else {
        do_parent(max);

        waitpid(pid, &status);
        printf("\n");
    }

    return 0;
}
