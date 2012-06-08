CUDAPATH=/usr/local/cuda
CC=clang

all:
	$(CC) -I$(CUDAPATH)/include -L$(CUDAPATH)/lib -lcuda cudadump.c -o cudadump

clean:
	-@rm cudadump
