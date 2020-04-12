#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

enum Const
{
	N_of_iterations = 1000000,
	N_of_processes = 6,
	Order = 1000000,
	Root = 0
};

void My_MpiGather(	void * sbuf, int scount, MPI_Datatype stype, 
					void * rbuf, int rcount, MPI_Datatype rtype, int root, MPI_Comm comm);

int main(int argc, char ** argv)
{
	double StartTime = 0, EndTime = 0;
	int ProcRank, ProcNum;
	double MeanError = 0;

    int SendBuf;
    int *RecvBuf = (int *)malloc(N_of_processes * sizeof(int));

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
	    My_MpiGather(	&SendBuf, 1, MPI_INT, 
	    				RecvBuf, 1, MPI_INT, 0, MPI_COMM_WORLD); 
    }

	MPI_Barrier(MPI_COMM_WORLD);

	if(ProcRank == 0)
	{
        EndTime = MPI_Wtime();
        MeanError = MPI_Wtick();
        printf("MeanError * 10^6 =  %.3lf\n", MeanError * Order);
        printf("GatherTime * 10^6 =  %.3lf\n", (EndTime - StartTime) * Order / N_of_iterations);
    }
	
	MPI_Finalize();
	return 0;
}

void My_MpiGather(	void * sbuf, int scount, MPI_Datatype stype, 
					void * rbuf, int rcount, MPI_Datatype rtype, int root, MPI_Comm comm)
{
	if((stype != MPI_INT) && (rtype != MPI_INT))
	{
		printf("Bad MPI_Datatype. Choose MPI_INT, please.\n");
		return;
	}
	int ProcNum = 0, ProcRank = 0;
	MPI_Status Status;
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	if(ProcRank == root)
	{
		for(int i = 0; i < ProcNum; i++)
		{
			if(i != root)
				MPI_Recv(	(void *)&(((int *)rbuf)[i]), rcount, rtype, i,
							0, comm, &Status);
			else
				((int *)rbuf)[i] = *(int *)sbuf;
		}
	}
	else
	{
		MPI_Send(	&sbuf, scount, stype, 
					root, 0, comm);
		//printf("recv %d from id = %d\n", *(int *)rbuf, ProcRank);
	}
}
