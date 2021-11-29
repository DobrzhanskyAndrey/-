#include "pt4.h"
#include "mpi.h"

template<class T>
void send(int t, int dest, MPI_Datatype  d)
{
    T val;
    pt >> val;
    MPI_Send(&val, 1, d, dest, t, MPI_COMM_WORLD);
       
}

template<class T>
void recv(MPI_Datatype d) 
{
    T val;
    MPI_Recv(&val, 1, d, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    pt << val;
}

void Solve()
{
    
    Task("MPI2Send22");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    {
        int t;
        for (int i = 1; i < size; i++)
        {
            pt >> t;
            if (t == 0)
                send<int>(t, i, MPI_INT);
            else 
                send<double>(t, i, MPI_DOUBLE);
        }
    }
    else
    {
        MPI_Status s;
        MPI_Probe(0, MPI_ANY_TAG, MPI_COMM_WORLD, &s);
        if (s.MPI_TAG == 0)
            recv<int>(MPI_INT);
        else recv<double>(MPI_DOUBLE);
    }
}
