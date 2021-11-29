#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI4Type12");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int sz = sizeof(int) * 2 + sizeof(double);
    char* rbuf = new char[sz];
    int pos;
    double val;
    int *arr = new int[2];

    if (rank > 0)
    {
        for (int i = 0; i < 2; i++)
            pt >> arr[i];
        pt >> val;

        pos = 0;
        MPI_Pack(arr, 2, MPI_INT, rbuf, sz, &pos, MPI_COMM_WORLD);
        MPI_Pack(&val, 1, MPI_DOUBLE, rbuf, sz, &pos, MPI_COMM_WORLD);
    }

    int all_sz = sz * (size - 1);
    char* unpack = new char[all_sz];
    MPI_Gather(rbuf, sz, MPI_PACKED, unpack, sz, MPI_PACKED, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        pos = sz;
        for (int i = 1; i < size; i++)
        {
            MPI_Unpack(unpack, sz, &pos, arr, 2, MPI_INT, MPI_COMM_WORLD);
            MPI_Unpack(unpack, sz, &pos, &val, 1, MPI_DOUBLE, MPI_COMM_WORLD);
            for (int i = 0; i < 2; i++)
                pt << arr[i];
            pt << val;
        }
    }
}
