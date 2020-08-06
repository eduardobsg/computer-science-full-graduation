#include <iostream>
#include <queue>
#include <string.h>
#include <string>

using namespace std;
 
int I, J, D = 4, C = 5, LEFT = 0, RIGHT = 1, kase = 1;
int dy[] = { -1, 0, +1, 0 };
int dx[] = { 0, +1, 0, -1 };
 
struct Position {
    int i, j, d, c, w;

    Position() {}
    
    Position(int X, int Y, int D, int C, int W) { 
    	i = X, j = Y, d = D, c = C, w = W; 
    }
 
    bool equals(Position o) { 
    	return i == o.i && j == o.j && c == o.c; 
    }
    
    bool valid() { 
    	return j < J && i < I && j >= 0 && i >= 0; 
    }
 
    Position* forward() {
    	return new Position(i + dy[d], j + dx[d], d, (c + 1) % C, w + 1);
    }
    
    Position* turn(int dir) {
    	return new Position(i, j, (d + 1 + dir * 2) % D, c, w + 1);
    }
};

string st(bool a) {
    return a ? "true" : "false";
}

int main() {

    while(cin >> I >> J) {
        
        if(I == 0 && J == 0) 
        	break;
        	
        cout << (kase > 1 ? "\n" : "") << "Case #" << kase << endl;
        kase++;
        
        char g[I][J], v[I][J][D][C]; // d[M][N][Direction][Color];
        memset(v, 0, sizeof v);
        Position start, end, ans = NULL;

        for(int i = 0; i < I; i++)
            for(int j = 0; j < J; j++) {
                cin >> g[i][j];
                if(g[i][j] == 'S') 
                	start = Position(i, j, 0, 0, 0);
                if(g[i][j] == 'T') 
                	end = Position(i, j, 0, 0, 0);
            }
            
        queue<Position> que;
        que.push(start);
        
        while(que.size()) {

            Position u = que.front(); 
            int i = u.i, j = u.j, c = u.c, d = u.d, w = u.w; 
            que.pop();

            if(u.equals(end)) { 
            	ans = u; 
            	break; 
            }
            
            if(!u.valid() || v[i][j][d][c] || g[i][j] == '#') 
            	continue;
            
            v[i][j][d][c] = 1;
            
            que.push(*u.turn(LEFT));
            que.push(*u.turn(RIGHT));
            que.push(*u.forward());
        }
        
        if(ans)
        	cout << "minimum time = " << ans.w << " sec" << endl;
        else
        	cout << "destination not reachable" << endl;
    }
    
    return 0;
}

