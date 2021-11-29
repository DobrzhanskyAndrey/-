#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI3Coll24");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int* rbuf = new int[1];
    int* scounts = new int[size];
    int* a = new int[size];
    int val;
    for (int i = 0; i < size; i++)
    {
        pt >> val;
        a[i] = val;
        scounts[i] = 1;
    }

    MPI_Reduce_scatter(a, rbuf, scounts, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    pt << rbuf[0];
}
