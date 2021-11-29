#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm15");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n = size / 2;
    MPI_Comm comm;
    int dims[] = { 2, n }, periods[] = { 0, 0 };
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &comm);
    MPI_Comm comm_sub;
    int remain_dims[] = { 0, 1 };
    MPI_Cart_sub(comm, remain_dims, &comm_sub);
    MPI_Comm_size(comm_sub, &size);
    MPI_Comm_rank(comm_sub, &rank);
    double a;
    if (rank == 0)
    {
        pt >> a;
    }
    MPI_Bcast(&a, 1, MPI_DOUBLE, 0, comm_sub);
    pt << a;
    
}
