//http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=497

#include <iomanip>
#include <iostream>

#define NORTH 100
#define SOUTH 200
#define WEST  300	 
#define	EAST  400	 	

using namespace std;

int main() {

	int b, w;	

	while(cin >> b >> w) {
		if(b == 0 && w == 0)		
			break; //finaliza o programa

		//cout << "b = " << b << ", w = " << w << endl;

		int squares[b][w];
		int maze[b][w];
		int robot_position[2];
		int robot_start[2];
		int robot_direction;		

		//south west corner
		robot_start[0] = b - 1;
		robot_start[1] = 0;

		robot_position[0] = b - 1;
		robot_position[1] = 0;
		robot_direction = EAST;
 
		//lê labirinto
		for(int i = 0; i < b; i++) {
			int maze_line;
			cin >> maze_line;
			//cout << maze_line << endl;

			for(int j = w - 1; j >= 0; j--) {
				if(maze_line % 10 == 0) {
					maze[i][j] = 0;
					squares[i][j] = 0; //posição visitável
				}
				else {
					maze[i][j] = 1;
					squares[i][j] = -1; //posição não visitável
				}
			
				//cout << "maze[" << i << "][" << j << "] = " << maze[i][j] << endl;
				//sleep(1);

				maze_line = (int) maze_line / 10;
			}			
		}

		//imprime o labirinto 
		/*
		cout << "Maze: " << endl;
		for(int i = 0; i < b; i++) {
			for(int j = 0; j < w; j++) {
				cout << maze[i][j] << " ";
			}
			cout << endl;
		}
		
		cout << "Squares: " << endl;
		for(int i = 0; i < b; i++) {
			for(int j = 0; j < w; j++) {
				cout << squares[i][j] << " ";
			}
			cout << endl;
		}
		*/

		//movimento
		while(robot_position[0] != robot_start[0] || 
			  robot_position[1] != robot_start[1] || 
		      squares[robot_start[0]][robot_start[1]] == 0) {

			//cout << robot_position[0] << "," << robot_position[1] << ". Direction = " << robot_direction << endl;
			//sleep(1);

			switch(robot_direction) {
				case EAST: 	if(robot_position[0] == (b - 1) || maze[robot_position[0] + 1][robot_position[1]] == 1) {
								//não precisa checar lateral direita ou já tem parede na direita, e precisa checar se é possível avançar
								if(robot_position[1] == (w - 1) || maze[robot_position[0]][robot_position[1] + 1] == 1) {
									robot_direction = NORTH;	
								}
								else if(maze[robot_position[0]][robot_position[1] + 1] == 0) {
									squares[robot_position[0]][robot_position[1]] = squares[robot_position[0]][robot_position[1]] + 1;
									robot_position[1] = robot_position[1] + 1;
								}
							}								
							else {
								//não tem parede, trocar direção do movimento e avançar se possível
								robot_direction = SOUTH; //trocar direção do movimento
								if(maze[robot_position[0] + 1][robot_position[1]] == 0) {
									squares[robot_position[0]][robot_position[1]] = squares[robot_position[0]][robot_position[1]] + 1;
									robot_position[0] = robot_position[0] + 1;
								}
							}

							break;
				case WEST: if(robot_position[0] == 0 || maze[robot_position[0] - 1][robot_position[1]] == 1) {
								if(robot_position[1] == 0 || maze[robot_position[0]][robot_position[1] - 1] == 1) {
									robot_direction = SOUTH;
								}								
								else if(maze[robot_position[0]][robot_position[1] - 1] == 0) {
									squares[robot_position[0]][robot_position[1]] = squares[robot_position[0]][robot_position[1]] + 1;
									robot_position[1] = robot_position[1] - 1;
								}						
							}								
							else {
								robot_direction = NORTH;
								if(maze[robot_position[0] - 1][robot_position[1]] == 0) {
									squares[robot_position[0]][robot_position[1]] = squares[robot_position[0]][robot_position[1]] + 1;
									robot_position[0] = robot_position[0] - 1;
								}
							}

							break;
				case SOUTH: if(robot_position[1] == 0 || maze[robot_position[0]][robot_position[1] - 1] == 1) {
								if(robot_position[0] == (b - 1) || maze[robot_position[0] + 1][robot_position[1]] == 1) {
									robot_direction = EAST;
								}								
								else if(maze[robot_position[0] + 1][robot_position[1]] == 0) {
									squares[robot_position[0]][robot_position[1]] = squares[robot_position[0]][robot_position[1]] + 1;
									robot_position[0] = robot_position[0] + 1;
								}						
							}								
							else {
								robot_direction = WEST;
								if(maze[robot_position[0]][robot_position[1] - 1] == 0) {
									squares[robot_position[0]][robot_position[1]] = squares[robot_position[0]][robot_position[1]] + 1;
									robot_position[1] = robot_position[1] - 1;
								}
							}

							break;
				case NORTH: if(robot_position[1] == (w - 1) || maze[robot_position[0]][robot_position[1] + 1] == 1) {
								if(robot_position[0] == 0 || maze[robot_position[0] - 1][robot_position[1]] == 1) {
									robot_direction = WEST;
								}	
								else if(maze[robot_position[0] - 1][robot_position[1]] == 0) {
									squares[robot_position[0]][robot_position[1]] = squares[robot_position[0]][robot_position[1]] + 1;
									robot_position[0] = robot_position[0] - 1;
								}						
							}								
							else {
								robot_direction = EAST;
								if(maze[robot_position[0]][robot_position[1] + 1] == 0) {
									squares[robot_position[0]][robot_position[1]] = squares[robot_position[0]][robot_position[1]] + 1;
									robot_position[1] = robot_position[1] + 1;
								}
							}

							break;
			}

		}

		//mostrar qunatidade de peças visitadas
		int zero = 0, one = 0, two = 0, three = 0, four = 0;
		
		for(int i = 0; i < b; i++) {
			for(int j = 0; j < w; j++) {
				switch(squares[i][j]) {
					case 0: zero++; 	break;
					case 1: one++; 		break;
					case 2: two++;		break;
					case 3: three++; 	break;
					case 4: four++; 	break;
				}
			}
		}
		
		cout << setw(3) << right << zero;
		cout << setw(3) << right << one;
		cout << setw(3) << right << two;
		cout << setw(3) << right << three;
		cout << setw(3) << right << four;
		cout << endl;
	}

	return 0;
}

