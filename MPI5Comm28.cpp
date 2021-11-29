#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm28");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

   

    int n = (size - 1) / 2;
    int* index = new int[size],
        * edges = new int[2 *(size - 1)];
    index[0] = n;
    for (int i = 1; i < size; i++)
    {
        i % 2 == 1 ? index[i] = index[i - 1] + 2 : index[i] = index[i - 1] + 1;
    }
    int j = 1;
    for (int i = 0; i < n; i++)
    {
        edges[i] = j;
        j += 2;
    }
    j = n;
    for (int i = 1; i < size; i++)
    {
        if (i % 2 == 1)
        {
            edges[j++] = 0;
            edges[j++] = i + 1;
        }
        else
        {
            edges[j++] = i - 1;
        }
    }

    MPI_Comm g_comm;
    MPI_Graph_create(MPI_COMM_WORLD, size, index, edges, 0, &g_comm);

    int count;
    MPI_Graph_neighbors_count(g_comm, rank, &count);
    int* neighbors = new int[count];
    MPI_Graph_neighbors(g_comm, rank, count, neighbors);

  
    int a = 0, b = 0;
    pt >> a;

    MPI_Status s;

    if (rank == 0)
    {
        for (int i = 0; i < count; i++)
        {

            MPI_Recv(&b, 1, MPI_INT, neighbors[i], 0, g_comm, &s);
            MPI_Send(&a, 1, MPI_INT, neighbors[i], 0, g_comm);
            pt << b;
        }
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            MPI_Send(&a, 1, MPI_INT, neighbors[i], 0, g_comm);
            MPI_Recv(&b, 1, MPI_INT, neighbors[i], 0, g_comm, &s);
            pt << b;
        }
    }

    delete[] index;
    delete[] edges;
    delete[] neighbors;

}
