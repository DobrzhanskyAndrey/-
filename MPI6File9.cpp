#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI6File9");
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

    MPI_File f;
    MPI_File_open(MPI_COMM_WORLD, name, MPI_MODE_RDONLY, MPI_INFO_NULL, &f);

   
        MPI_Offset offset, step = rank * sizeof(int);
        MPI_File_get_size(f, &offset);
        int filesz = offset / sizeof(int);
        MPI_File_seek(f, step, MPI_SEEK_SET);
        int readsz = min(rank + 1, filesz - rank);
        int* arr = new int[readsz];
        MPI_Status s;
        MPI_File_read_all(f, arr, readsz, MPI_INT, &s);
        for (int i = 0; i < readsz; i++)
        {
            pt << arr[i];
        }
        delete arr;
        
    MPI_File_close(&f);

}
