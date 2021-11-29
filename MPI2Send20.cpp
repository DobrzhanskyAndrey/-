#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send20");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double val = 0.0;
    if (rank > 0)
    {
        int n;
        pt >> val;
        pt >> n;
        MPI_Send(&val, 1, MPI_DOUBLE, 0, n, MPI_COMM_WORLD);
    }
    else
    {
        for (int i = 1; i < size; i++)
        {
            MPI_Recv(&val, 1, MPI_DOUBLE, MPI_ANY_SOURCE, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            pt << val;
        }
    }
}
