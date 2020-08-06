//http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2454

#include <iostream>

using namespace std;

int main() {

int numberOfCases, numberPlayers, numberSnakes, numberDice, diceRoll, j;
bool gameOver = false;

	cin >> numberOfCases;
	for (int i =0; i < numberOfCases; i++)
	{
		gameOver = false;
		cin >> numberPlayers;
		int player[numberPlayers];
		cin >> numberSnakes;
		int snakes[numberSnakes][2];
		cin >> numberDice;
		
		for (j = 0; j < numberPlayers; j++)
		{
			player[j] = 1;
		}
		
		for (j =0; j < numberSnakes; j++)
		{
			cin >> snakes[j][0];
			cin >> snakes[j][1];
		}
		
		for(j = 0; numberDice > 0 && gameOver == false; j++, numberDice--) {
			
			cin >> diceRoll;
			player[j] = player[j] + diceRoll;

			for(int k= 0; k < numberSnakes; k++)
			{
				if (player[j] == snakes[k][0])
				{
					player[j] = snakes[k][1];
				}
			}
			
			if (player[j] > 99)
			{
				player[j] = 100;
				gameOver = true;
			}
			
			if(j == (numberPlayers-1))
				j = -1;
		}
		
		for (; numberDice > 0; numberDice--)
		{
			int a;
			cin >> a;
		}
			
		for (j = 0; j < numberPlayers; j++)
		{
			cout << "Position of player " << j+1 << " is " << player[j] << "." << endl;
		}
				
	}
	return 0;
}
