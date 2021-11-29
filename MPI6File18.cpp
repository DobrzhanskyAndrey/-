#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI6File18");
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

    int n = 0;
    pt >> n;
    
    MPI_File f;
    MPI_File_open(MPI_COMM_WORLD, name, MPI_MODE_WRONLY, MPI_INFO_NULL, &f);

    char native[7] = "native";
    MPI_File_set_view(f, 5 * rank * sizeof(int), MPI_INT, MPI_INT, native, MPI_INFO_NULL);

    MPI_File_write_at_all(f, (n - 1), &rank, 1, MPI_INT, MPI_STATUS_IGNORE);
    
    MPI_File_close(&f);
}
