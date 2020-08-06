#include <iomanip>
#include <iostream>
#include <cstdlib>

#define ROWS 6

using namespace std;

//Variável global
int **mat;

int sum_matrix(int rows, int cols) {

	int total_sum = 0;	
	for(int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++)
			total_sum += mat[i][j];
			
	return total_sum;
}


int main() {

	//allocando linhas
	mat = (int **) malloc(sizeof(int) * ROWS);

	for(int i = 0; i < 3; i++) {
	
		//allocando colunas
		int cols = ROWS*(i+1);
		for(int a = 0; a < ROWS; a++) 
			mat[a] = (int *) malloc(sizeof(int) * cols);

		//inserindo conteúdo na matriz e imprimindo
		cout << "Case " << i+1 << ": " << endl;
		for(int j = 0; j < ROWS; j++) {
			for(int k = 0; k < cols; k++) {
				mat[j][k] = j*k;
			    cout << setw(4) << right << mat[j][k];				
			}
			cout << endl;
		}			

		int total_sum = sum_matrix(ROWS, cols);
		cout << "Total: " << total_sum << endl << endl;

		//desalocando colunas
		for(int j = 0; j < ROWS; j++)
			free(mat[j]);
		
	}

	return 0;
}
