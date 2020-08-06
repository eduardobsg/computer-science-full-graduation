#include <iostream>
#include <vector>
using namespace std;

int p, b, c;

int main()
{
	int T; cin >> T;
	while (T--)
	{
		cin >> p >> b >> c;
		int v[110] = {0};
		for (int i = 0; i < 110; ++i) v[i] = i;
		
		int x,y;
		for (int i = 0; i < b; ++i)
		{
			cin >> x >> y;
			v[x] = y;
		}
		
		int end = 0, dado, player = 0;
		vector<int> pos(p, 1);
		for (int i = 0; i < c; ++i)
		{
			cin >> dado;
			if (end) continue;
			
			pos[player] += dado;
			pos[player] = v[ pos[player] ];
			if ( pos[player] >= 100 )
			{
				pos[player] = 100;
				end = 1;
			}
			
			player = (player+1)%p;
		}
		
		for (int i = 0; i < p; ++i)
			cout << "Position of player " << i+1 << " is " << pos[i] << "." << endl;
	}
}

