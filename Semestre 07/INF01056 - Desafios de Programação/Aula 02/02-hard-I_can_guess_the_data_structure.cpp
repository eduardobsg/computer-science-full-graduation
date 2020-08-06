#include <iostream>
#include <cstdio>
#include <queue>
#include <stack>

using namespace std;

int main() {
	
	int a;
	while( (cin >> a) && a != EOF ) {

		bool flag_q, flag_pq, flag_s;
		flag_q = flag_pq = flag_s = true;
	
		queue<int> q; //q.push(); q.pop(); q.front();
		priority_queue<int> pq; //pq.push(); pq.pop(); pq.top();
		stack<int> s; //s.push(); s.pop(); s.top();
		
		int op, val; //operation, value
		for(int i = 0; i < a; i++) {
			cin >> op >> val;
			
			switch(op) {
				case 1: q.push(val); 
						pq.push(val); 
						s.push(val);
						break;

				case 2: if(flag_q) {
							if(!q.empty() && (val == q.front()))
								q.pop();
							else
								flag_q = false;
						}
						
						if(flag_pq) {
							if(!pq.empty() && (val == pq.top()))
								pq.pop();
							else
								flag_pq = false;
						}
						
						if(flag_s) {
							if(!s.empty() && (val == s.top()))
								s.pop();
							else
								flag_s = false;
						}		
						
						break;						 
			}
		}
		
        //cout << flag_q << flag_pq << flag_s << endl;
		
		if(flag_q + flag_pq + flag_s > 1)
			cout << "not sure" << endl;
		else if(flag_q)	
			cout << "queue" << endl;
		else if(flag_pq)
			cout << "priority queue" << endl;
		else if(flag_s)
			cout << "stack" << endl;	
		else
			cout << "impossible" << endl;		
	}

	return 0;
}
