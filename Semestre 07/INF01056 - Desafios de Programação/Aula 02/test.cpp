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
        for(int i = 0; i < a; ++i) {
            cin >> op >> val;
            
            switch(op) {
				case 1: q.push(val);
                		pq.push(val);
                		s.push(val);
                		break;
                		
                case 2: flag_s &= !s.empty() && s.top() == val;
                		flag_q &= !q.empty() && q.front() == val;
				        flag_pq &= !pq.empty() && pq.top() == val;
				        if(flag_pq) pq.pop();
				        if(flag_q) q.pop();
				        if(flag_s) s.pop();
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

