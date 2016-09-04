#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>

typedef struct Arg {
    long long beg;
    long long end;
    long long *nums;
    long long *med;
} Arg;

/* aperacoes das threads */
void* thr_fun(void *arg_) {
    long long i;
    Arg *arg = (Arg*) arg_;

    /* preenche o vetor */
    for(i = arg->beg; i < arg->end; i++) {
        arg->nums[i] = rand() % 1001;
    }

    /* soma os valores */
    *(arg->med) = 0;
    for(i = arg->beg; i < arg->end; i++) {
        *(arg->med) += arg->nums[i];
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    long long i, med;
    Arg arg;
    if(argc != 3) {
        perror("numero errado de argumentos");
        exit(1);
    }
    int N = *argv[1];
    int K = *argv[2];
    long long size = N*1024*1024;
    long long *meds;
    pthread_t *threads;

    /* aloca memoria */
    arg.nums = (long long*) malloc(size * sizeof (long long));
    threads = (pthread_t*) malloc(K * sizeof (pthread_t));
    meds = (long long*) malloc(K * sizeof (long long));

    /* cria threads */
    srand(time(NULL));
    for(i = 0; i < K; i++) {
        arg.beg = i*(size/K);
        arg.end = (i+1)*(size/K);
        arg.med = (meds + i);
        if(arg.end > size) arg.end = size;
        pthread_create(&threads[i],NULL,thr_fun,(void*)&arg);
    }
    for(i = 0; i < K; i++) {
        pthread_join(threads[i],NULL);
    }

    /* calcula a media */
    med = 0;
    for(i = 0; i < K; i++) {
            med += meds[i];
    }
    med /= size;
    printf("%lld\n",med);

    /* libera memoria */
    free(arg.nums);
    free(threads);
    free(meds);

    pthread_exit(NULL);

    return 0;
}
