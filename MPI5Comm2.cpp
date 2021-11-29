#include "pt4.h"
#include "mpi.h"

void Solve()
{
    Task("MPI5Comm2");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Group group;
    MPI_Comm_group(MPI_COMM_WORLD, &group);
    MPI_Group newgroup;
    int ranks = (size + 1) / 2;
    int* arr = new int[ranks];
    for (int i = 0; i < ranks; i++)
    {
        arr[i] = 2 * i;
    }
    MPI_Group_excl(group, ranks, arr, &newgroup);
    MPI_Comm newcomm;
    MPI_Comm_create(MPI_COMM_WORLD, newgroup, &newcomm);

    if (newcomm == MPI_COMM_NULL)
    {
        return;
    }
    ShowLine(rank);
    
        double* sbuf = new double[2];
        double val = 0.0;
        for (int i = 0; i < 2; i++)
        {
            pt >> val;
            sbuf[i] = val;
        }
        MPI_Comm_size(newcomm, &size);
        double* rbuf = new double[size * 2];
        MPI_Allgather(sbuf, 2, MPI_DOUBLE, rbuf, 2, MPI_DOUBLE, newcomm);
        for (int i = 0; i < size * 2; i++)
        {
            pt << rbuf[i];
        }
    
}
