#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI6File25");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char name[12];
    if (rank == 0)
        pt >> name;
    MPI_Bcast(name, 12, MPI_CHAR, 0, MPI_COMM_WORLD);

    int sz = 3 * (rank + 1), val = 0;
    int * numbers= new int[sz];
    for (int i = 0; i < sz; i++)
    {
        pt >> val;
        numbers[i] = val;
    }

    MPI_File f;
    MPI_File_open(MPI_COMM_WORLD, name, MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &f);

    MPI_Datatype type;
    MPI_Type_vector(3, (rank + 1), ((1 + size) * size) / 2, MPI_INT, &type);

    char native[7] = "native";
    MPI_File_set_view(f, (((1 + rank) * rank) / 2) * sizeof(int), MPI_INT, type, native, MPI_INFO_NULL);

    MPI_File_write_all(f, numbers, sz, MPI_INT, MPI_STATUS_IGNORE);

    MPI_File_close(&f);

}


