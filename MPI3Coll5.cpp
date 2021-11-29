#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI3Coll5");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int* a = new int[rank + 2];
    int val = 0;
    int* rec_buf = new int[(size + 3) * size / 2];
    for (int i = 0; i < rank + 2; i++)
    {
        pt >> val;
        a[i] = val;
    }
    int* rcounts = new int[size];
    int* displs = new int[size];
    int x = 0;
    for (int i = 0; i < size; i++)
    {
        rcounts[i] = i + 2;
        displs[i] = x;
        x += rcounts[i];
    }
    MPI_Gatherv(a, rank + 2, MPI_INT, rec_buf, rcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        for (int i = 0; i < (size + 3) * size / 2; i++)
        {
            pt << rec_buf[i];
        }
    }
}
