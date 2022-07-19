/*
	Programul citeste din 2 fisiere (matrix1.txt si matrix2.txt)
	2 matrici si returneaza intr-un alt fisier suma celor 2 matrici.
	Prima varianta dar nu salveaza decat in 2 variabile temporare 
	elementele din fisiere,  a doua varianta, salveaza in 2 matrici.
*/
#include<stdio.h>

int main(){
    FILE* matrix1 = fopen("matrix1.txt", "r");
	FILE* matrix2 = fopen("matrix2.txt", "r");
	FILE* matrix3 = fopen("matrix3.txt", "w");
	FILE* matrix4 = fopen("matrix4.txt", "w");
    int n1, m1, n2, m2;
	
	fscanf(matrix1, "%d", &n1);
	fscanf(matrix1, "%d", &m1);
	fscanf(matrix2, "%d", &n2);
	fscanf(matrix2, "%d", &m2);
	
	int v[3]={0,1,2};
	printf("%d %d %d %d %d\n\n\n", v[1], v, &v, &*v, *(&v));
	//varianta 1
	int temp1, temp2;
	fprintf(matrix4, "%d %d \n", n1, m1);
	for(int i = 0; i< n1*m1; i++){
		fscanf(matrix1, "%d", &temp1);
		fscanf(matrix2, "%d", &temp2);
		if(i !=0 && i % m1 == 0)
			fprintf(matrix4, "\n");
		fprintf(matrix4, "%d ", temp1+temp2);
	}
	fclose(matrix4);
	
	rewind(matrix1);
	rewind(matrix2);
	
	//varianta 2 (salveaza din fisier in matrici)
	fscanf(matrix1, "%d", &n1);
	fscanf(matrix1, "%d", &m1);
	fscanf(matrix2, "%d", &n2);
	fscanf(matrix2, "%d", &m2);
	
    int v1[n1][m1];
	int v2[n2][m2];

	for(int i=0; i<n1; i++)
    {
        for(int j=0; j<m1; j++)
        {
            fscanf(matrix1, "%d", &v1[i][j]);
        }
    }

	for(int i=0; i<n2; i++)
    {
        for(int j=0; j<m2; j++)
        {
            fscanf(matrix2, "%d", &v2[i][j]);
        }
    }

	for(int i=0; i<n1; i++)
    {
        for(int j=0; j<m1; j++)
        {
            printf("%d", v1[i][j]);
			printf("%s", " ");
		}
		printf("\n");
    }
	
	printf("\n");

	for(int i=0 ;i<n2; i++)
    {
        for(int j=0; j<m2; j++)
        {
            printf("%d", v2[i][j]);
			printf("%s", " ");
		}
		printf("\n");
    }

	printf("\n");
	
	fprintf(matrix3, "%d %d \n", n1, m1);
	for(int i=0; i<n1; i++) {
		for(int j=0; j<m1; j++) {
			fprintf(matrix3, "%d", v1[i][j]+v2[i][j]);
			fprintf(matrix3, "%s", " ");

			printf("%d", v1[i][j]+v2[i][j]);
			printf(" ");
		}
		fprintf(matrix3,"\n");
		printf("\n");
	}
	fclose(matrix3);
    return 0;
}
