# Задание
Написать собственную реализацию 4-х коллективных функций (из 2 обязательной задачи), используя парные пересылки сообщений и MPI_Barrier. Измерить их время работы с точностью порядка точности MPI_Wtime.

## Результаты

`time_my_broadcast` = (2,8 +- 1) mcs
`time_my_reduce` = (2,6 +- 1) mcs
`time_my_scatter` = (2,7 +- 1) mcs
`time_my_gather` = (2,9 +- 1) mcs