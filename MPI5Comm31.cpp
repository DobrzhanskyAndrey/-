#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm31");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n = size - size / 3;
    int* src = new int[n], * degr = new int[n];

    for (int i = 0; i < n; i += 2)
    {
        degr[i] = 3;
        degr[i + 1] = 1;
    }

    for (int i = 0, j = 0; i < n; i += 2, j += 3)
    {
        src[i] = j;
        src[i + 1] = j + 1;
    }

    int dest_size = (size / 3) * 4;
    int* dest = new int[dest_size];

    int cur = 0, k = 0;
    for (int i = 0; i < dest_size; ++i)
    {
        if (k < 3)
        {
            dest[i] = (src[cur] + k + 1) % size;
            k++;
        }
        else
        {
            cur++;
            k = 0;
            dest[i] = src[cur] + 1;
            cur++;
        }
    }

    MPI_Comm distcomm;
    if (rank == 0)
    {
        MPI_Dist_graph_create(MPI_COMM_WORLD, n, &src[0], &degr[0], &dest[0], MPI_UNWEIGHTED, MPI_INFO_NULL, 0, &distcomm);
    }
    else
    {
        MPI_Dist_graph_create(MPI_COMM_WORLD, 0, &src[0], &degr[0], &dest[0], MPI_UNWEIGHTED, MPI_INFO_NULL, 0, &distcomm);
    }

    int* wd = new int[0];
    int* sw = new int[0];
    int w = 0;
    int in_dg, out_dg;
    MPI_Dist_graph_neighbors_count(distcomm, &in_dg, &out_dg, &w);
    int* new_src = new int[in_dg];
    int* new_dest = new int[out_dg];
    MPI_Dist_graph_neighbors(distcomm, in_dg, &new_src[0], MPI_UNWEIGHTED, out_dg, &new_dest[0], MPI_UNWEIGHTED);

    int a = 0, b = 0;
    pt >> a;
    int sum = a;
    for (int i = 0; i < out_dg; i++)
    {
        MPI_Send(&a, 1, MPI_INT, new_dest[i], 0, distcomm);
    }

    for (int i = 0; i < in_dg; i++)
    {
        MPI_Recv(&b, 1, MPI_INT, new_src[i], 0, distcomm, MPI_STATUS_IGNORE);
        sum += b;
    }

    pt << sum;
}
