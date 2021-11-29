#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm9");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm comm;
    int n = 0;
    pt >> n;
    int color = n == 1 ? 0 : MPI_UNDEFINED;
    MPI_Comm_split(MPI_COMM_WORLD, color, rank, &comm);
    if (comm == MPI_COMM_NULL)
    {
        return;
    }
    MPI_Comm_size(comm, &size);
    double a = 0.0;
    pt >> a;
    double* rbuf = new double[size];
    MPI_Allgather(&a, 1, MPI_DOUBLE, rbuf, 1, MPI_DOUBLE, comm);
    for (int i = 0; i < size; i++)
    {
        pt << rbuf[i];
    }
}
