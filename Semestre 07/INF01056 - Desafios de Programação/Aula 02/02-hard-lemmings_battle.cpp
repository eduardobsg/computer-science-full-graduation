#include <iostream>
#include <queue>

using namespace std;

int main() {
	
	int cases, flag_first = 1;
	cin >> cases;

	int num_fields, green, blue;
	priority_queue<int> soldiers_g;
	priority_queue<int> soldiers_b;

	for(int i = 0; i < cases; i++) {			
		cin >> num_fields >> green >> blue;
	
		int winners[num_fields];
		for(int j = 0; j < num_fields; j++)
			winners[j] = 0;
	
		int power;
		while(green--) {
			cin >> power;
			soldiers_g.push(power);
		}			
		while(blue--) {
			cin >> power;
			soldiers_b.push(power);
		}

		
		while(!soldiers_g.empty() && !soldiers_b.empty()) {

			int g, b;
			for(int j = 0; j < num_fields; j++) {
				if(soldiers_g.empty() || soldiers_b.empty())
					break;

				g = soldiers_g.top(); 
				b = soldiers_b.top();
				soldiers_g.pop();
				soldiers_b.pop();				

				if(g == b)
					winners[j] = 0;
				else
					winners[j] = b - g; //negative -> green won; positive -> blue won
			}

			for(int j = 0; j < num_fields; j++) {
				if(winners[j] < 0)
					soldiers_g.push(winners[j] * -1);
				if(winners[j] > 0)			
					soldiers_b.push(winners[j]);
				winners[j] = 0;
			}

		}	
	
		if(flag_first)
			flag_first = 0;
		else
			cout << endl;

		if(soldiers_g.empty() && soldiers_b.empty())	
			cout << "green and blue died" << endl;
		else if(soldiers_g.empty()) {
			cout << "blue wins" << endl;
			while(!soldiers_b.empty()) {
				cout <<	soldiers_b.top() << endl;
				soldiers_b.pop();	
			}
		}
		else if(soldiers_b.empty()) {
			cout << "green wins" << endl;
			while(!soldiers_g.empty()) {
				cout <<	soldiers_g.top() << endl;
				soldiers_g.pop();	
			}
		}	
	}
		
	return 0;
}
