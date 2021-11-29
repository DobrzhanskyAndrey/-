#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send3");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int a[4];
    if (rank > 0)
    {
        int val;
        for (int i = 0; i < 4; i++)
        {
            pt >> val;
            a[i] = val;
        }
        MPI_Send(&a, 4, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Status s;
        for (int i = 1; i < size; i++)
        {
            MPI_Recv(&a, 4, MPI_INT, i, 0, MPI_COMM_WORLD, &s);
            for (int j = 0; j < 4; j++)
                pt << a[j];
        }
    }
    

   
}
