#include <stdio.h>
#include "mpi.h"

int main(int argc, char ** argv)
{
	int ProcRank, ProcNum, RecvRank;
	MPI_Status Status;
	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

	
	if(ProcRank == 0)
	{
		printf("Hello from process %d\n", ProcRank);
		fflush(stdout);

		for(int i = 1; i < ProcNum; i++)
		{

			MPI_Send(	NULL, 0, MPI_INT, i,
						0, MPI_COMM_WORLD);
			MPI_Recv(	NULL, 0, MPI_INT, i,
			 			MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
			
		}
	}
	else
	{
		MPI_Recv(	NULL, 0, MPI_INT, 0,
			 		MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
		printf("Hello from process %d\n", ProcRank);
			fflush(stdout);
		MPI_Send(	NULL, 0, MPI_INT, 0,
					0, MPI_COMM_WORLD);	
	}


	MPI_Finalize();
	return 0;
}