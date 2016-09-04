sequencial: sequencial.c
	gcc sequencial.c -o sequencial

thread: thread.c
	gcc -pthread thread.c -o thread

process: process.c
	gcc -lrt process.c -o process

test: sequencial thread process
	eval time ./sequencial 64
	eval time ./thread 64 4
	eval time ./process 64 4

run: test

clean:
	rm -f sequencial thread process
