all: build run

build:
	mpicc main.c -std=c11 -Wall -o a.out
run:
	mpirun -np 24 ./a.out 100000	
clean:
	rm -rf *.o a.out	