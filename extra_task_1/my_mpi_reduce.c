#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

enum Const
{
	N_of_iterations = 1000000,
	Order = 1000000,
	Root = 0
};



void My_MpiReduce(	void * sendbuf, void * recvbuf, int count, 
					MPI_Datatype type, MPI_Op op, int root, MPI_Comm comm);

int main(int argc, char ** argv)
{
	double StartTime = 0, EndTime = 0;
	int ProcRank, ProcNum;
	double MeanError = 0;
	int Result = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	MPI_Barrier(MPI_COMM_WORLD);
	
	if(ProcRank == Root)
	{
    	StartTime = MPI_Wtime();
	}

	for(int i = 0; i < N_of_iterations; i++)
	{
        My_MpiReduce(&ProcRank, &Result, 1, MPI_INT, MPI_SUM, Root, MPI_COMM_WORLD);
	}

	MPI_Barrier(MPI_COMM_WORLD);

	if(ProcRank == Root)
	{
		printf("Result = %d\n", Result);
        EndTime = MPI_Wtime();
        MeanError = MPI_Wtick();
        printf("MeanError * 10^6 =  %.3lf\n", MeanError * Order);
        printf("ReduceTime * 10^6 =  %.3lf\n", (EndTime - StartTime) * Order / N_of_iterations);
    }
	
	MPI_Finalize();
	return 0;
}

void My_MpiReduce(	void * sendbuf, void * recvbuf, int count, 
					MPI_Datatype type, MPI_Op op, int root, MPI_Comm comm)
{
	/*	I've done MPI_Reduce only for MPI_INT, because I need to allocate
		extra memory of certain type.*/
	if(type != MPI_INT)
	{
		printf("Bad MPI_Datatype. Choose MPI_INT, please.\n");
		return;
	}
	int ProcNum = 0, ProcRank = 0;
	MPI_Status Status;
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	//MPI_Barrier(MPI_COMM_WORLD);

	if(ProcRank == root)
	{
		/*int **intermediate_recvbuf = (int **)malloc(count * sizeof(int*));
		for(int i = 0; i < count; i++)
			intermediate_recvbuf[i] = (int *)calloc(ProcNum * sizeof(int), 0);
		int *result_recvbuf = (int *)calloc(count * sizeof(int), 0);*/
		int intermediate_recvbuf[count][ProcNum];
		memset(intermediate_recvbuf, 0, count * ProcNum * sizeof(int));
		int result_recvbuf[count];
		memset(result_recvbuf, 0, count * sizeof(int));

		for(int i = 0; i < ProcNum; i++)
		{
			if(i != root)
			{
				MPI_Recv(recvbuf, count, type, i, 0, comm, &Status);
				//printf("recv from id = %d\n", i);
				for(int j = 0; j < count; j++)
				{
					intermediate_recvbuf[j][i] = ((int *)recvbuf)[j];
					//printf("recvbuf = %d\n", intermediate_recvbuf[j][i]);
				}
			}
			else
			{
				for(int j = 0; j < count; j++)
				{
					intermediate_recvbuf[j][i] = ((int *)sendbuf)[j];
					//printf("sendbuf = %d from id = %d\n", intermediate_recvbuf[j][i], ProcRank);
				}
			}
				
		}

		if(op == MPI_SUM)
	    {

	    	for(int i = 0; i < count; i++)
	    	{
	    		((int *)recvbuf)[i] = 0;
	    		for(int j = 0; j < ProcNum; j++)
		    	{
					((int *)recvbuf)[i] += intermediate_recvbuf[i][j];
					//printf("int_recvbuf = %d\n", intermediate_recvbuf[i][j]);
		    	}
	    	}
	    }	
		else
			printf("Please, choose MPI_SUM operation. Others will be added soon.\n");
			
		/*for(int i = 0; i < count; i++)
			printf("%d\n", result_recvbuf[i]);
		// save nature
		free(result_recvbuf);
		for(int i = 0; i < count; i++)
			free(intermediate_recvbuf[i]);
		free(intermediate_recvbuf);*/
	}
	else
	{
		MPI_Send(sendbuf, count, type, root, 0, comm);
		//printf("sended, my id = %d\n", ProcRank);
	}
		
}

