#include <mpi.h>
#include <stdio.h>

double f(double x) {
	return 4.0 / (1 + x * x);
}

int main(int argc, char** argv) {
	double sumq = 0, pi = 0,start=0,end=0;
	int n;
	MPI_Init(NULL, NULL);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	if (world_rank == 0) {
		scanf_s("%d", &n);
		for (int i = 1; i < world_size; i++) {
			MPI_Send(&n, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
		start = MPI_Wtime();
	}
	else {
		MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

	for (int i = 1; i <= (n - n % world_size); i += world_size) {
		sumq += f((i + world_rank - 0.5) / n);
	}
	if (n % world_size != 0) {
		for (int j = 0; j < (n % world_size); j++) {
			if (j == world_rank) {
				sumq += f(((n - n % world_size + j + 0.5)) / n);
			}
		}
	}

	if (world_rank != 0) {
		MPI_Send(&sumq, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}
	else {
		pi = sumq;
		for (int i = 1; i < world_size; i++) {
			MPI_Recv(&sumq, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			pi += sumq;
		}
	}
	if (world_rank == 0) {
		end = MPI_Wtime();
		pi /= n;
		printf("pi = %0.15f\n", pi);
		printf("%f", end - start);
	}
	MPI_Finalize();
}