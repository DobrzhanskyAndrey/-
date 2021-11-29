#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm24");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int m = 0, n = 0;
    if (rank == 0)
        pt >> m >> n;

    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int x = 0;
    int y = 0;
    if (rank < m * n)
        pt >> x >> y;

    MPI_Comm dcomm;
    int dims[] = { m, n }, periods[] = { 0, 1 };
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &dcomm);

    if (dcomm != MPI_COMM_NULL)
    {
        int coords[] = { x, y };
        int nrank;
        if (!MPI_Cart_rank(dcomm, coords, &nrank))
            pt << nrank;
        else
            pt << -1;
    }

}
