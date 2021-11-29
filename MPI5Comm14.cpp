#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm14");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int n;

	if (rank == 0)
		pt >> n;

	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

	int* dims = new int[2];
	dims[0] = n;
	dims[1] = size / n;

	int* periods = new int[2];
	periods[0] = 0;
	periods[1] = 0;

	MPI_Comm comm;
	MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, false, &comm);

	if (comm == MPI_COMM_NULL)
	{
		return;
	}
	int coords[2];
	MPI_Cart_coords(comm, rank, 2, coords);
	pt << coords[0] << coords[1];
	
}
