#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

typedef struct Arg {
    long long beg;
    long long end;
    long long *nums;
    long long *med;
} Arg;

/* preenche vetor */ 
void fill(Arg *arg) {
        long long i;

        for(i = arg->beg; i < arg->end; i++) {
            arg->nums[i] = rand() % 1001;
        }
}

/* soma valores */
void sum(Arg *arg) {
        long long i;

        *(arg->med) = 0;
        for(i = arg->beg; i < arg->end; i++) {
            *(arg->med) += arg->nums[i];
        }
}

int main(int argc, char *argv[]) {
    long long i, med;
    Arg arg;
    pid_t pid;
    if(argc != 3) {
        perror("numero errado de argumentos");
        exit(1);
    }
    int N = strtol(argv[1],NULL,10);
    int K = strtol(argv[2],NULL,10);
    long long size = N*1024*1024;

    /* aloca memoria e cria area compartilhada */
    int fd = shm_open("vetor_numeros", O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("shm_open");
        exit(-1);
    }
    ftruncate(fd, (size + K)*64);
    arg.nums = (long long*)mmap(0, (size + K)*64, PROT_READ | PROT_WRITE, MAP_SHARED,  fd, 0);

    srand(time(NULL));
    /* cria processos */
    arg.beg = 0;
    arg.end = size/K;
    arg.med = (arg.nums + size);
    for(i = 1; i < K; i++) {
        pid = fork();
        if(pid == 0) {
            arg.beg = i*(size/K);
            arg.end = (i+1)*(size/K);
            arg.med = (arg.nums + size + i);
            if(arg.end > size) arg.end = size;
        } else break;
    }
    fill(&arg);
    sum(&arg);
    int status;
    if(i != K) wait(&status);
    if(i != 2) exit(0);

    /* calcula a media */
    med = 0;
    for(i = 0; i < K; i++) {
            med += arg.nums[size + i];
    }
    med /= size;
    printf("%lld\n",med);

    /* libera memoria */
    munmap(arg.nums, (size + K)*64);
    shm_unlink("vetor_numeros");

    return 0;
}
