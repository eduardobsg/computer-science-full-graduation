/*

c() = 	{
			se alt = 0: 
			 
			se alt > 0 && alt < 9:
			se alt = 9:	
		}

*/


#include<iostream>

using namespace std;

int a;
int max_alt;

int calc_cost( int cost[10][a], int final_cost, int i, int j ) {
	
	if(j == 9) {
		if(i == 0)
			return final_cost;
		else {
			max_alt = max_alt - 1;
			calc_cost( cost, 0, 0, 0 );
		}
	}
		
	if(i == 0) {
		if( cost[i][j+1]+30 < cost[i+1][j+1]+60 )
			calc_cost(cost, final_cost + cost[i][j+1]+30, i, j+1);
		else	
			calc_cost(cost, final_cost + cost[i+1][j+1]+60, i+1, j+1);
	}	
	else if(i == max_alt) {
		if( cost[i][j+1]+30 < cost[i-1][j+1]+20 )
			calc_cost(cost, final_cost + cost[i][j+1]+30, i, j+1);
		else	
			calc_cost(cost, final_cost + cost[i-1][j+1]+20, i-1, j+1);
	}
	else {
		if( cost[i][j+1]+30 <= cost[i-1][j+1]+20 && cost[i][j+1]+30 < cost[i+1][j+1]+60 )
			calc_cost(cost, final_cost + cost[i][j+1]+30, i, j+1);
		else if( cost[i-1][j+1]+20 < cost[i][j+1]+30 && cost[i-1][j+1]+20 < cost[i+1][j+1]+60 )
			calc_cost(cost, final_cost + cost[i-1][j+1]+20, i-1, j+1);
		else if( cost[i+1][j+1]+60 < cost[i][j+1]+30 && cost[i+1][j+1]+60 < cost[i-1][j+1]+20 )	
			calc_cost(cost, final_cost + cost[i-1][j+1]+20, i-1, j+1);
	}
}


int main() {

	int cases;
	
	cin >> cases;
	for(int k = 0; k < cases; k++) {
		
		int miles;
		
		cin >> miles;
		//cout << "miles:" << miles << endl;
		
		int mat[10][miles/100];
		a = miles/100;
		for(int i = 0; i < 10; i++) {
			for(int j = 0; j < a; j++)
				cin >> mat[i][j];
		}
		
		/*
		cout << "matrix: " << endl;
		for(int i = 0; i < 10; i++) {
			for(int j = 0; j < a; j++)
				cout << mat[i][j] << " ";
			cout << endl;
		}
		*/
		
		
		int cost[10][a];
		for(int i = 0; i < 10; i++) {
			for(int j = 0; j < a; j++) {
				if(mat[i][j] < 0)
					cost[i][j] = mat[i][j] * -1;
				else if(mat[i][j] > 0)
					cost[i][j] = mat[i][j] * -1;	
				else 
					cost[i][j] = 0;
			}
		}	
		
		cout << "cost: " << endl;
		for(int i = 0; i < 10; i++) {
			for(int j = 0; j < a; j++)
				cout << cost[i][j] << " ";
			cout << endl;
		}
		
		max_alt = 9;
		final_cost = calc_cost( cost, 0, 0, 0 );
		cout << final_cost << endl << endl;				
	}

	return 0;
}
