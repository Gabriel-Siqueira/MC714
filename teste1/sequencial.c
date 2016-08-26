#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <error.h>

int main(int argc, char *argv[]) {
	long long i,med;
	if(argc == 2) {
		int N = *argv[1];
		long long size = N*1048576;
		long long *nums;

		/* aloca memoria */
		nums = (long long*) malloc(size * sizeof (long long));

		/* preenche vetor */ 
		srand (time(NULL));
		for(i = 0; i < size; i++) {
			nums[i] = rand() % 1001;
		}

		/* calcula e imprime a media */
		med = 0;
		for(i = 0; i < size; i++) {
			med += nums[i];
		}
		med /= size;
		printf("%lld\n",med);
    }

	return 0;
}
