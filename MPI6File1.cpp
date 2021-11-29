#include "pt4.h"
#include "mpi.h"
#include <vector>

using namespace std;

void Solve()
{
    Task("MPI6File1");
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
    int val = 0, arr[2];

    MPI_File f;
    MPI_File_open(MPI_COMM_WORLD, name, MPI_MODE_RDONLY, MPI_INFO_NULL, &f);

    if (rank != 0)
    {
        int n = 0;
        pt >> n;
        vector<int> numbers;
        for (int i = 0; i < n; i++)
        {
            pt >> val;
            numbers.push_back(val);
        }
        MPI_Status stat;
        for (int i = 0; i < numbers.size(); i++)
        {
            MPI_Offset offset;
            MPI_File_read_at(f, (numbers[i] - 1) * sizeof(int), &val, 1, MPI_INT, &stat);
            if (stat.count != 0)
            {
                pt << val;
            }
        }

    }
    MPI_File_close(&f);
}
