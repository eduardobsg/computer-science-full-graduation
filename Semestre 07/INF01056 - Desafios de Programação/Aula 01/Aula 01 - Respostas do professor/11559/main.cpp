#include <iostream>
using namespace std;

int n, b, h, w, p, a;

int main()
{
	while (cin >> n >> b >> h >> w)
	{
		int ret = 2000000000;
		for (int i = 0; i < h; ++i)
		{
			cin >> p;
			for (int j = 0; j < w; ++j)
			{
				cin >> a;
				if ( a >= n ) ret = min(ret, p*n);
			}
		}
		
		if (ret > b) cout << "stay home" << endl;
		else cout << ret << endl;
	}
}

