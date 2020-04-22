# Task 3 (Sum a row using parallel computations)

Calculate sum of a row `6/(PI^2 * x^2)` from `1` to `n`. `n` is an input argument. At the root of the process, it is necessary to process the arguments and send to the rest of the processes the parameters for the calculation. Simultaneously perform calculations and collect the results at the root process, taking into account the calculated IEEE754 standards, minimizing error. Also display the running time of the count.

## Results

Input parameters:
	`length` = 100000;
	`Number of iterations` = 20;	//to compute time more presice
	`Multiply` = 1 << 6;			// sum of big numbers computes more presice 

Result:
	I used barriers at each iteration, so computing_time is bigger(~ 0.3 us without them)

	`Number of processes` = 24;
	Result row from 1 to 100 = 0.865452;
	computing_time = 7.885 us;

	`Number of processes` = 20;
	Result row from 1 to 100000 = 0.999878;
	computing_time = 6.731 us;

	`Number of processes` = 24;
	Result row from 1 to 100000 = 0.999854;
	computing_time = 7.832 us;

	`Number of processes` = 20;
	`Multiply` = 1;
	Result row from 1 to 100000 = 0.999878;
	computing_time = 6,784 us;


In result, it is not so important to check `Multiply` parameter in our task, but if a summation is computed on extremely small numbers, the result will be incorrect(-nan in our case). 	