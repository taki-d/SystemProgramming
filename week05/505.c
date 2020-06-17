#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

volatile sig_atomic_t sig = 0;

void signal_handler(int s) {
    if(s == SIGALRM){
        sig = -2;
    }else if(s == SIGINT){
        sig = -3;
    }else{
        printf("something wrom\n");
    }
}

int mygetchar(int sec, int usec) {
    int input;

    struct sigaction sa_sig;
    struct itimerval itimer;

    memset(&sa_sig, 0, sizeof(sa_sig));
    sa_sig.sa_handler = signal_handler;

    if(sigaction(SIGINT, &sa_sig, NULL) < 0) {
        perror("sigaction");
        exit(1);
    }

    if (sigaction(SIGALRM, &sa_sig, NULL) < 0) {
        perror("sigaction");
        exit(1);
    }

    itimer.it_value.tv_sec = itimer.it_interval.tv_sec = sec;
    itimer.it_value.tv_usec = itimer.it_interval.tv_usec = usec;

    if (setitimer(ITIMER_REAL, &itimer, NULL) < 0) {
        perror("setiitimer");
        exit(1);
    }

    input = getchar();

    if(sig != 0) {
        input = sig;
    }

    itimer.it_value.tv_sec  = itimer.it_interval.tv_sec  = 0;
    itimer.it_value.tv_usec = itimer.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &itimer, NULL) < 0) {
        perror("setitimer");
        exit(1);
    }

    return input;
}

int main(int argc, char* argv[])
{
    time_t time_;

    if(argc < 3) {
        printf("too few argments\n");
        exit(1);
    }

    int sec = atoi(argv[1]);
    int usec = atoi(argv[2]);
//    int sec = 5;
//    int usec = 10;

    time(&time_);
    printf("%s", ctime(&time_));

    int rt =  mygetchar(sec, usec);

    time(&time_);
    printf("%s", ctime(&time_));

    if(rt > 0) {
        printf("%c\n", rt);
    } else {
        printf("%d\n", rt);
    }

    return 0;

}


