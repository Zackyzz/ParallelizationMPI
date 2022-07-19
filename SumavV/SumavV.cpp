#include <mpi.h>
#include <stdio.h>
#include <stdlib.h> 

int main(int argc, char** argv) {
	double start = 0, start2 = 0, end = 0, end2 = 0;
	int world_size, world_rank, n, sumq = 0, total = 0;
	int* data = NULL;
	FILE* dataset = fopen("C:/Users/desktop/source/repos/SumavV/dataset.txt", "r");
	fscanf(dataset, "%d", &n);

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	if (world_rank == 0) {
		data = (int*)malloc(n * sizeof(int));
		for (int i = 0; i < n; i++) {
			fscanf(dataset, "%d", &data[i]);
		}
		start = MPI_Wtime();
		for (int i = n / world_size, j = 1; j < world_size; i += n / world_size, j++) {
			MPI_Send(&data[i], n / world_size, MPI_INT, j, 0, MPI_COMM_WORLD);
		}
	}
	else {
		data = (int*)malloc(n / world_size * sizeof(int));
		MPI_Recv(data, n / world_size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

	start2 = MPI_Wtime();
	for (int i = 0; i < n / world_size; i++) {
		sumq += data[i];
	}
	end2 = MPI_Wtime() - start2;

	if (world_rank != 0) {
		MPI_Send(&sumq, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	else {
		start2 = MPI_Wtime();
		for (int i = 0; i < n % world_size; i++) {
			sumq += data[n - n % world_size + i];
		}
		end2 += MPI_Wtime() - start2;
		total = sumq;
		for (int i = 1; i < world_size; i++) {
			MPI_Recv(&sumq, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			total += sumq;
		}
		end = MPI_Wtime() - start;
		printf("The total sum is %d and was computed in %f seconds - communication included.\nOverall it took %f seconds to compute the sum by each process.",
			total, end, end2);
	}
	MPI_Finalize();
}