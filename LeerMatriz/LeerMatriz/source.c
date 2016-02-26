//reads formatted matrix protocol: d <num_rows> <num_columns>, r <col[0]> <col[1]>, ... 
//date: 10/02/2015
//Modificado y resuelto por Mario Pedraza

#include <stdio.h>
#include <stdlib.h>

#define SIZE_OF_LINE 250

void print_matrix(int ** matriz, int n, int m)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
			printf("%d\t", matriz[i][j]);
		
		printf("\n");
	}
}

void free_matrix(int n, int m, int ** matrix)
{
	// free dynamically allocated memory
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m;j++)
			free (matrix[i][j]);
	}
	// delete actual matrix
	free (matrix);
}

int** read_matrix(const char* filename, int* n, int* m)
{
	int i, row=0;
	int **matrix=NULL;
	char line[SIZE_OF_LINE], token; 

	FILE * f=fopen(filename,"r");
	if( f==NULL) {
		puts("error when opening file");
		return 0;
	}

	while(!feof(f)){
		//protocol (extracts headers)
		fscanf(f, "%c",&token);

		//protocol using swith-case
		switch(token)
		{
		case 'd':
		{
			fscanf(f, " %d %d", &n, &m);
			break;
		}
		case 'r':
		{
			for (i = 0; i < n;i++)
				fscanf(f, " %d", matrix[row][i]);
			row++;
			break;
		}
		default:
			perror("unrecognized protocol");
			return NULL;
		}

	}
	return matrix;
}


void main(){
//client application
	int n, m;
	int ** matrix=read_matrix("matriz.txt", &n, &m);
	
	print_matrix(matrix, n, m);
	free_matrix(n, m, matrix);
}