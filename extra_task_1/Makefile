target_bcast: build_bcast run_bcast
target_reduce: build_reduce run_reduce
target_scatter: build_scatter run_scatter
target_gather: build_gather run_gather	

build_bcast:
	mpicc my_mpi_bcast.c -std=c11 -Wall -o bcast
build_reduce:
	mpicc my_mpi_reduce.c -std=c11 -Wall -o reduce
build_scatter:
	mpicc my_mpi_scatter.c -std=c11 -Wall -o scatter
build_gather:
	mpicc my_mpi_gather.c -std=c11 -Wall -o gather	

run_bcast:
	mpirun -np 6 ./bcast	
run_reduce:
	mpirun -np 6 ./reduce
run_scatter:
	mpirun -np 6 ./scatter	
run_gather:
	mpirun -np 6 ./gather	

clean:
	rm -rf *.o bcast reduce scatter gather

