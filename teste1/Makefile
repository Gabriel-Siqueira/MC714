N=64
K=4

sequencial: sequencial.c
	gcc sequencial.c -o sequencial

thread: thread.c
	gcc -pthread thread.c -o thread

process: process.c
	gcc -lrt process.c -o process

test: sequencial thread process
	eval time ./sequencial $(N)
	eval time ./thread $(N) $(K)
	eval time ./process $(N) $(K)

run: test

clean:
	rm -f sequencial thread process
