#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void sigsegv_action(int signum, siginfo_t *info, void *ctx){
    printf("signal handler called: sigsegv\n");
    printf("caused by accessing address 0x%x\n", info->si_addr);

    exit(1);
}

void sigfpe_action(int signum, siginfo_t *info, void *ctx){
    printf("signal handler called: sigfpe\n");
    exit(1);
}

int main(int argc, char *argv[])
{

    if(argc < 2){
        printf("too few argments\n");
        return 0;
    }
    int action = atoi(argv[1]);

    struct sigaction sa_sigsegv;
    struct sigaction sa_sigfpe;

    memset(&sa_sigsegv, 0, sizeof(sa_sigsegv));
    sa_sigsegv.sa_sigaction = sigsegv_action;
    sa_sigsegv.sa_flags = SA_RESTART | SA_SIGINFO;

    memset(&sa_sigfpe, 0, sizeof(sa_sigfpe));
    sa_sigfpe.sa_sigaction = sigfpe_action;
    sa_sigfpe.sa_flags = SA_RESTART | SA_SIGINFO;

    if (sigaction(SIGSEGV, &sa_sigsegv, NULL) < 0) {
        perror("sigaction");
        exit(1);
    }

    if (sigaction(SIGFPE, &sa_sigfpe, NULL) < 0) {
        perror("sigaction");
        exit(1);
    }

    if(action == 0){
        const char *s = "hello world";
        char *sa = s;
        *sa = 'H';
    }else{
        //sigfpe
        int a = 0, b = 100, c;
        c = b / a;
        printf("%d\n", c);
    }

    return 0;
}

