#include <iostream>
#include <vector>

using namespace std;

long int n, m;
vector<int> vessels(1005);

bool valid(int mid)
{
	int used=1, actual=0;
	for(int i=0; i<n; i++)
	{
		if(actual+vessels[i] <=mid)
		{
			actual+=vessels[i];
		}
		else
		{
			actual=vessels[i];
			used++;
		}
	}
	return used <=m;
}

int main()
{
	while(cin >> n >> m)
	{
		int hi=0, lo=0, mid;
		for(long int i=0; i<n; i++)
		{
			cin >> vessels[i];
			if(lo<vessels[i])
				lo=vessels[i];
			hi+=vessels[i];
		}
		while(lo<hi)
		{
			mid=(lo+hi)/2;
			if(valid(mid))
			{
				hi=mid;
			}
			else
			{
				lo=mid+1;
			}
		}
		cout << lo << endl;
	}
}
