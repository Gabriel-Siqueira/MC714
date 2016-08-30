#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>

void* fill(void *arg) {
		long long beg = *((long long**)arg)[0];
		long long end = *((long long**)arg)[1];
		long long *nums = ((long long**)arg)[2];
		long long i;
		for(i = beg; i < end; i++) {
			nums[i] = rand() % 1001;
		}
		return NULL;
}

void* sum(void *arg) {
		long long beg = *((long long**)arg)[0];

		long long end = *((long long**)arg)[1];
		long long *nums = ((long long**)arg)[2];
		long long *med = ((long long**)arg)[2];
		long long i;

		*med = 0;
		for(i = beg; i < end; i++) {
			*med += nums[i];
		}
		
		return NULL;
}

int main(int argc, char *argv[]) {
	long long i,med,beg,end;
	long long *arg[4];
	if(argc == 3) {
		int N = *argv[1];
		int K = *argv[2];
		long long size = N*1048576;
		long long *nums,*meds;
		pthread_t **threads;

		/* aloca memoria */
		nums = (long long*) malloc(size * sizeof (long long));
		threads = (pthread_t**) malloc(K * sizeof (pthread_t*));
		meds = (long long*) malloc(K * sizeof (long long));

		/* preenche vetor */ 
		srand(time(NULL));
		for(i = 0; i < K; i++) {
			beg = i*(size/K);
			end = (i+1)*(size/K);
			if(end > size) end = size;
			arg[0] = &beg;
			arg[1] = &end;
			arg[2] = nums;
			pthread_create(threads[i],NULL,fill,(void*)arg);
		}
		for(i = 0; i < K; i++) {
			pthread_join(*threads[i],NULL);
		}

		/* calcula e imprime a media */
		for(i = 0; i < K; i++) {
			beg = i*(size/K);
			end = (i+1)*(size/K);
			if(end > size) end = size;
			arg[0] = &beg;
			arg[1] = &end;
			arg[2] = nums;
			arg[3] = &(meds[i]);
			pthread_create(threads[i],NULL,sum,(void*)arg);
		}
		for(i = 0; i < K; i++) {
			pthread_join(*threads[i],NULL);
		}
		med = 0;
		for(i = 0; i < K; i++) {
				med += meds[i];
		}
		med /= size;
		printf("%lld\n",med);
    }

	return 0;
}
