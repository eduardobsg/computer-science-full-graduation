#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;


int gcd(int a, int b)
{
	int aux;
	while(b!=0)
	{
		aux=b;
		b=a%b;
		a=aux;
	}
	return a;
}

int main()
{
	
	int cases;
	cin >> cases;

	char aux;
	scanf("%c", &aux);

	for(int i = 0; i < cases; i++) {

		//cout << "case " << i << endl;	

		char entry[10000];
		int count = -1;
		do {
			count++;	
			scanf("%c", &entry[count]);	
		} while(entry[count] != '\n');

		entry[count] = '\0';

		vector<int> entries;
		char * pch;
		pch = strtok(entry, " ");
	 	while(pch != NULL) {
    		//printf("%s\n", pch);
			entries.push_back(atoi(pch));
			//cout << entries.back() << endl;
    		pch = strtok (NULL, " ,.-");
  		}
  		
  		int maxgcd=1;
		for(int i=0; i<entries.size(); i++)
		{
			for(int j=i+1; j<entries.size(); j++)
			{
				int gcdiv=gcd(entries[i], entries[j]);
				if(gcdiv>maxgcd)
					maxgcd=gcdiv;
			}
		}
	cout << maxgcd << endl;
	}
	
	
}
