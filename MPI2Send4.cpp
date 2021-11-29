#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send4");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int val = 0;
    int n = 0;
    if (rank != 0)
    {
        pt >> n;
        int* arr = new int[n];
        byte* buf = new byte[4 * n + MPI_BSEND_OVERHEAD];
        MPI_Buffer_attach(buf, 4 * n + MPI_BSEND_OVERHEAD);
        for (int i = 0; i < n; i++)
        {
            pt >> val;
            arr[i] = val;
        }
        MPI_Bsend(arr, n, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else
    {
        int* arr = new int[5];
        for (int i = 1; i < size; i++)
        {
            MPI_Status s;
            MPI_Probe(0, 0, MPI_COMM_WORLD, &s);
            int count;
            MPI_Get_count(&s, MPI_INT, &count);
            Show(count);
            MPI_Recv(arr, count, MPI_INT, i, 0, MPI_COMM_WORLD, &s);
            for (int j = 0; j < count; j++)
            {
                pt << arr[j];
            }
        }
    }
}
