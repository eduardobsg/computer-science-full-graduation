#include <iostream>
#include <cstdio>
#include <new>
#include <queue>

#define GREEN	1
#define WHITE 	2
#define BLUE	3 
#define RED		4
#define BLACK	5

#define END 	999
 
int colors[5] = {1, 2, 3, 4, 5};
int direction[4] = {0, 1, 2, 3}; //Oeste: 0, Norte: 1, Leste: 2, Sul: 3

int maze_lin, maze_col;
int **maze;

int start[2];
int end[2];

using namespace std;

/*
int forward(int position[], int dir) {
	
	if(dir == 0) {
		
	}
		

	return val;
}
*/

int min_path(int start[]) {
	
	int current[3]; //[0] e [1]: posição no maze; [2]: direção 
	int path;
	
	/*
	while(1) {
		
	}
	*/
	
	
	/*
	cout << "start: " << start[0] << "," << start[1] << endl;
	
	for(int i = 0; i < maze_lin; i++) {
		for(int j = 0; j < maze_col; j++)		
			printf("%d\t", maze[i][j]);
		cout << endl;
	}	
	cout << endl;
	*/
	
	
	return path; //retorna para a main
}

void test_reachability(int start[], int end[]) {

	queue< pair<int, int> > q;
	pair<int, int> p;
	bool visited[maze_lin * maze_col];
	for(int i = 0; i < maze_lin * maze_col; i++)
		visited[i] = false;
	
	q.push( make_pair(start[0], start[1]) );
	while(!q.empty()) {
		
		cout << ".";
		
		p = q.front(); q.pop();
		visited[p.first*maze_col + p.second] = true;
		
		if(p.first == end[0] && p.second == end[1]) {
			cout << endl << "T is reachable." << endl;
			return;
		}
		else {
			if( (p.second - 1) >= 0 && visited[(p.first)*maze_col + p.second - 1] != true && maze[p.first][p.second - 1] != -1)
				q.push( make_pair(p.first, p.second - 1) );	
			if( (p.second + 1) < maze_col && visited[(p.first)*maze_col + p.second + 1] != true && maze[p.first][p.second + 1] != -1)
				q.push( make_pair(p.first, p.second + 1) );		
			if( (p.first - 1) >= 0 && visited[(p.first - 1)*maze_col + p.second] != true && maze[p.first - 1][p.second] != -1)
				q.push( make_pair(p.first - 1, p.second) );				
			if( (p.first + 1) < maze_lin && visited[(p.first + 1)*maze_col + p.second] != true && maze[p.first + 1][p.second] != -1)
				q.push( make_pair(p.first + 1, p.second) );							
		}
			
	}
	
	cout << "T is not reachable." << endl;
	return;				
}


int main() {

	while( (cin >> maze_lin >> maze_col) && maze_lin != 0 && maze_col != 0 ) {
		
		maze = new int*[maze_lin];
		for(int i = 0; i < maze_lin; i++) 
			maze[i] = new int[maze_col];
		
		for(int i = 0; i < maze_lin; i++) {
			char in; 
			for(int j = 0; j < maze_col; j++) {
				cin >> in;
				
				if(in == '#')
					maze[i][j] = -1;
				else {
					maze[i][j] = 1;
					if(in == 'S') {
						start[0] = i;
						start[1] = j;
					}
					else if(in == 'T') {
						maze[i][j] = END;
						end[0] = i;
						end[1] = j;
					}		
				}
			}
		}
		
		test_reachability(start, end);
		
		//min_path(start);
	
		delete [] maze;
		
	}

	return 0;
}

















