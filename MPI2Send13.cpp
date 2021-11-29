#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send13");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int s_val = 0;
    int r_val = 0;
    pt >> s_val;  
    if (rank > 0)
    {
        MPI_Ssend(&s_val, 1, MPI_INT, (size + rank - 1) % size, 0, MPI_COMM_WORLD);
        MPI_Recv(&r_val, 1, MPI_INT, (size + rank + 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    else
    {
        MPI_Recv(&r_val, 1, MPI_INT, (size + rank + 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Ssend(&s_val, 1, MPI_INT, (size + rank - 1) % size, 0, MPI_COMM_WORLD);
    }
    pt << r_val;
}
