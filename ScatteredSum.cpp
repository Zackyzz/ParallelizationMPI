#define _CRT_SECURE_NO_WARNINGS
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int world_size, world_rank, sumq = 0, total = 0, n;
	double time = 0, time2 = 0;
	FILE* dataset = fopen("C:/Users/desktop/source/repos/SumavV/dataset.txt", "r");
	fscanf(dataset, "%d", &n);

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	int* data = NULL;
	int* solo = (int*)malloc(n / world_size * sizeof(int));

	if (world_rank == 0) {
		data = (int*)malloc(n * sizeof(int));
		for (int i = 0; i < n; i++) {
			fscanf(dataset, "%d", data+i);
		}
	}

	time = MPI_Wtime();
	MPI_Scatter(data, n / world_size, MPI_INT, solo, n / world_size, MPI_INT, 0, MPI_COMM_WORLD);

	time2 = MPI_Wtime();
	for (int i = 0; i < n / world_size; i++) {
		sumq += *(solo + i);
	}
	time2 = MPI_Wtime() - time2;

	MPI_Reduce(&sumq, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (world_rank == 0) {
		for (int i = n - n % world_size; i < n; i++) {
			total += *(data + i);
		}
		printf("The sum is %d, which took %f s.\nThe computation itself without communication took %f s.",
			total, MPI_Wtime() - time, time2);
	}
	MPI_Finalize();
}