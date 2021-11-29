#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send17");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int s_val = 0;
    //if (rank > 0)
    {
        for (int i = 0; i < size; i++)
        {
            if (i != rank)
            {
                pt >> s_val;
                MPI_Send(&s_val, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }
        for (int i = 0; i < size; i++)
        {
            if (i != rank)
            {
                MPI_Recv(&s_val, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                pt << s_val;
            }
        }
    }
    /*else
    {
        for (int i = 1; i < size; i++)
        {
            MPI_Recv(&r_val, 1, MPI_INT, (rank + i) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            pt << r_val;
            pt >> s_val;
            MPI_Send(&s_val, 1, MPI_INT, (rank + i) % size, 0, MPI_COMM_WORLD);
        }
    }*/

}
