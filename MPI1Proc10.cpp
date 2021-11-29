#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI1Proc10");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int n;
    pt >> n;
    if (rank == 0 && size % 2 == 0)
    {
        double d_val, d_min;
        pt >> d_min;
        for (int i = 1; i < n; i++)
        {
            pt >> d_val;
            if (d_min > d_val)
                d_min = d_val;
        }
        pt << d_min;
    }
    else
    {
        if (rank % 2 == 0)
        {
            int i_val, i_min;
            pt >> i_min;
            for (int i = 1; i < n; i++)
            {
                pt >> i_val;
                if (i_min > i_val)
                    i_min = i_val;
            }
            pt << i_min;
        }
        else
        {
            double d_val, d_max;
            pt >> d_max;
            for (int i = 1; i < n; i++)
            {
                pt >> d_val;
                if (d_max < d_val)
                    d_max = d_val;
            }
            pt << d_max;
        }
    }
}
