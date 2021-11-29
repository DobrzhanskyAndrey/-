#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send6?");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    double val = 0;
    if (rank == 0)
    {
        byte* buf = new byte[8 + MPI_BSEND_OVERHEAD];
        MPI_Buffer_attach(buf, 8 + MPI_BSEND_OVERHEAD);
        for (int i = size - 1; i > 0; i--)
        {
            pt >> val;
            MPI_Bsend(&val, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Recv(&val, 1, MPI_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        pt << val;
    }
}
