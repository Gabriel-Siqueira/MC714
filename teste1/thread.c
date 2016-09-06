#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>

typedef struct Arg {
    long long beg;
    long long end;
    long long **nums;
    long long med;
} Arg;

/* aperacoes das threads */
void* thr_fun(void *arg_) {
    long long i;
    Arg *arg = (Arg*) arg_;

    /* preenche o vetor */
    for(i = arg->beg; i < arg->end; i++) {
        (*(arg->nums))[i] = rand() % 1001;
    }

    /* soma os valores */
    arg->med = 0;
    for(i = arg->beg; i < arg->end; i++) {
        arg->med += (*(arg->nums))[i];
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    long long i, med;
    Arg *args;
    if(argc != 3) {
        perror("numero errado de argumentos");
        exit(1);
    }
    int N = strtol(argv[1],NULL,10);
    int K = strtol(argv[2],NULL,10);
    long long size = N*1024*1024;
    long long *nums;
    pthread_t *threads;

    /* aloca memoria */
    nums = (long long*) malloc(size * sizeof (long long));
    threads = (pthread_t*) malloc(K * sizeof (pthread_t));
    args = (Arg*) malloc(K * sizeof (Arg));

    /* cria threads */
    srand(time(NULL));
    for(i = 0; i < K; i++) {
        args[i].beg = i*(size/K);
        args[i].end = (i+1)*(size/K);
        args[i].nums = &nums;
        if(args[i].end > size) args[i].end = size;
        pthread_create(&threads[i],NULL,thr_fun,(void*)&args[i]);
    }
    for(i = 0; i < K; i++) {
        pthread_join(threads[i],NULL);
    }

    /* calcula a media */
    med = 0;
    for(i = 0; i < K; i++) {
            med += args[i].med;
    }
    med /= size;
    printf("%lld\n",med);

    /* libera memoria */
    free(nums);
    free(threads);
    free(args);

    pthread_exit(NULL);

    return 0;
}
