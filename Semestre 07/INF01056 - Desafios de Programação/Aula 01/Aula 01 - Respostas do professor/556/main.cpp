#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int offset[4][2] = {{0,1},{-1,0},{0,-1},{1,0}};

int n, m;
vector<string> v;
vector< vector<int> > c;

bool isWall(pair<int,int> p)
{
	return ( p.first < 0 or p.second < 0 or
			 p.first == n or p.second == m or
			 v[p.first][p.second] == '1' );
}

int main()
{
	while (cin >> n >> m)
	{
		if (n == 0) break;
		v.resize(n);
		for (int i = 0; i < n; ++i) cin >> v[i];
		c = vector< vector<int> >(n, vector<int>(m, 0));
		
		pair<int,int> p(n-1, 0), q,r;
		int dir = 0;
		bool ok = 0;
		do
		{
			if (!ok)
			{
				c[p.first][p.second]++;
				ok = 1;
			}
			r = make_pair(p.first + offset[(dir+3)%4][0],p.second + offset[(dir+3)%4][1]);
			q = make_pair(p.first + offset[dir][0],p.second + offset[dir][1]);
			
			if (!isWall(r))
			{
				dir = (dir+3)%4;
				p = r;
				ok = 0;
			}
			else if ( isWall(q) )
			{
				dir = (dir+1)%4;
			}
			else
			{
				ok = 0; p = q;
			}
			
		} while (p != make_pair(n-1,0));
		
		vector<int> ret(5,0);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				if (v[i][j] != '1' and c[i][j] < 5) ret[ c[i][j] ]++;
		
		for (int i = 0; i < 5; ++i) printf("%3d", ret[i]);
		cout << endl;
	}
}

