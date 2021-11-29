#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm11");
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
    int color = n == 1 ?  0 : MPI_UNDEFINED;
    MPI_Comm_split(MPI_COMM_WORLD, color, rank, &comm);
    if (comm == MPI_COMM_NULL)
    {
        return;
    }
    double a = 0.0;
    pt >> a;
    double res = 0.0;
    MPI_Allreduce(&a, &res, 1, MPI_DOUBLE, MPI_SUM, comm);
    pt << res;


}
