//http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2595

#include <iostream>

using namespace std;

int main () { 
	long num_participants, budget, num_hotels, num_weeks;
	long hotel_price, available_beds;
	long min_value; //menor valor gasto

	while(cin >> num_participants >> budget >> num_hotels >> num_weeks) {
		min_value = budget + 1; //inicialização

		for(int i = 0; i < num_hotels; i++) {
			cin >> hotel_price;
			for(int j = 0; j < num_weeks; j++) {
				cin >> available_beds;
				if(available_beds >= num_participants)
					if(num_participants * hotel_price <= budget)
						if(num_participants * hotel_price < min_value)
							min_value = num_participants * hotel_price;
			}	
		}

		if(min_value == budget + 1)
			cout << "stay home" << endl;
		else
			cout << min_value << endl;
	}

	return 0; 
} 
