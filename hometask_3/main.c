#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <mpi.h>
#include <math.h>

enum Const
{
	Multiply = 1 << 6,	// sum of big numbers computes more presice 
	N_of_iterations = 20,
	Order = 1 << 6,
	Root = 0
};

#define M_PI 3.14159265358979323846 

double Calc_Row(long int length);

int main(int argc, char* argv[])
{
	double alpha = 6 / (M_PI * M_PI);
	double StartTime = 0.0, EndTime = 0.0;
	double result = 0.0;
	int ProcRank, ProcNum;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	// read length
	long int length = 0;
	if(ProcRank == 0)
	{
		if(argc != 2)
		{
			printf("Invalid number of input arguments!\n");
			exit(-1);
		}
		char* end;

		length = strtol(argv[1], &end, 10);
		if(length == LONG_MAX || length == LONG_MIN || length == 0)
		{
			printf("Invalid input. Please, check your length number!\n");
			exit(-1);
		}
	}

	MPI_Barrier(MPI_COMM_WORLD);
	if(ProcRank == 0)
	{
    	StartTime = MPI_Wtime();
	}
	for(int k = 0; k < N_of_iterations; k++)
	{
		double hidden_result = Calc_Row(length);
		MPI_Reduce(&hidden_result, &result, 1, MPI_DOUBLE, MPI_SUM, Root, MPI_COMM_WORLD);
		/*if(ProcRank == 0)
			printf("Result on %d iteration = %.6f\n", k, result);*/
		MPI_Barrier(MPI_COMM_WORLD);
	}
	
	if(ProcRank == 0)
	{
		result = result * alpha / Multiply; // don't forget that every member of a row have been computed with Multiply param
    	EndTime = MPI_Wtime();
    	printf("Result row from 1 to %ld = %.6f\n", length, result);
    	printf("computing_time = %.3lf us;\n", (EndTime - StartTime) * Order / N_of_iterations);
	}

	MPI_Finalize();
	return 0;
}

double Calc_Row(long int length)
{
	double hidden_result = 0.0;
	int ProcRank, ProcNum;

	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	
	long int interval = length / ProcNum;
	long int interval_begin = interval * ProcRank + 1;
	long int interval_end = interval_begin + interval;

	for(int i = interval_end - 1; i >= interval_begin; --i)
		hidden_result += Multiply / (double)(i * i);
	
	// last process computes all the rest elements of a row
	if(ProcRank == ProcNum - 1)
	{
		for(int j = length; j >= interval_end; --j)
			hidden_result += Multiply / (double)(j * j);
	}
	return hidden_result;
}
