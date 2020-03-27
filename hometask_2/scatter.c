#include <stdio.h>
#include <stdlib.h>
#include "mpich/mpi.h"

enum Const
{
	N_of_iterations = 1000000,
	N_of_array_elems = 3,
	Order = 1000000,
	Root = 0
};

int main(int argc, char ** argv)
{
	double StartTime = 0, EndTime = 0;
	int ProcRank, ProcNum;
	int Buffer = 0;
	double MeanError = 0;

    int RecvBuf;
    int *SendBuf = (int *)malloc(N_of_array_elems * sizeof(int));

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	MPI_Barrier(MPI_COMM_WORLD);
	
	if(ProcRank == 0)
	{
    	StartTime = MPI_Wtime();
	}

	for(int i = 0; i < N_of_iterations; i++)
	{
	    MPI_Scatter( SendBuf, 1, MPI_INT, 
	    			&RecvBuf, 1, MPI_INT, 0, MPI_COMM_WORLD); 
    }

	MPI_Barrier(MPI_COMM_WORLD);

	if(ProcRank == 0)
	{
        EndTime = MPI_Wtime();
        MeanError = MPI_Wtick();
        printf("MeanError * 10^6 =  %.3lf\n", MeanError * Order);
        printf("BroadcastTime * 10^6 =  %.3lf\n", (EndTime - StartTime) * Order / N_of_iterations);
    }
	
	MPI_Finalize();
	return 0;
}