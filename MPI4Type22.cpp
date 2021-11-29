#include "pt4.h"
#include "mpi.h"

void Solve()
{
    Task("MPI4Type22");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	double* a = new double[size - 1];
	double *out = new double[(size - 1) * (size - 1)];

	MPI_Datatype newtype;
	MPI_Type_create_resized(MPI_DOUBLE, 0, 8 * (size - 1), &newtype);
	MPI_Type_commit(&newtype);

	MPI_Datatype* stypes = new MPI_Datatype[size];
	MPI_Datatype* rtypes = new MPI_Datatype[size];
	for (int i = 0; i < size; i++)
	{
		stypes[i] = MPI_DOUBLE;
		rtypes[i] = newtype;
	}
	
	if (rank != 0)
	{
		for (int i = 0; i < size - 1; ++i)
		{
			pt >> a[i];
		}
	}

	int* scounts = (int*)malloc(4 * size);
	int* sdispls = (int*)malloc(4 * size);
	int* rcounts = (int*)malloc(4 * size);
	int* rdispls = (int*)malloc(4 * size);

	for (int i = 0; i < size; i++)
	{
		scounts[i] = size - 1;
		sdispls[i] = 0;

		rcounts[i] = size - 1;
		rdispls[i] = (i - 1) * 8;
	}
	rdispls[0] = 0;
	rdispls[1] = 0;

	MPI_Alltoallw(&a[0], scounts, sdispls, &stypes[0], &out[0], rcounts, rdispls, &rtypes[0], MPI_COMM_WORLD);

	if (rank == 0)
	{
		for (int i = 0; i < (size - 1) * (size - 1); i++)
		{
			pt << out[i];
		}
	}
}
