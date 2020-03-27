## Время работы коллективных функций MPI

Измерить время работы 4 коллективных функций MPI: MPI_Bcast, MPI_Reduce (для любой операции), MPI_Gather и MPI_Scatter. Добиться точности измерения порядка точности MPI_Wtime.
 
# Результаты

`BroadcastTime` = (0.591 +- 0.054) mks
`ReduceTime` = (1.259 +- 0.103) mks
`ScatterTime` = (0.320 +- 0.023) mks
`GatherTime` = (0.846 +- 0.075) mks

