#include <stdio.h>
#include "mpich/mpi.h"

enum Const
{
	N_of_iterations = 1000000,
	Order = 1000000,
	Root = 0
};

int main(int argc, char ** argv)
{
	double StartTime = 0, EndTime = 0;
	int ProcRank, ProcNum;
	int Buffer = 0;
	double MeanError = 0;

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
		if(ProcRank == 0)
		{
			Buffer = i;
		}

        MPI_Bcast(&Buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);    
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

