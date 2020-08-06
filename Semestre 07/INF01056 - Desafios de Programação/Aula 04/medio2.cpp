/*
Jefferson Stoffel
João Gross
*/

#include <iostream>

using namespace std;

int main(void)
{
	int m, n;

	cin >> m >> n;

	while((m > 0) && (n > 0)){
		
		bool visitedJunctions[m];
		
		int i;
		for(i = 0; i < m; i++){
			visitedJunctions[i] = false;
		}

		int roads[n][3];

		int totalCost = 0;
		
		for(i = 0; i < n; i++){
			cin >> roads[i][0] >> roads[i][1] >> roads[i][2];
			totalCost += roads[i][2];
		}

		int minimumSpanningTreeCost = 0;
		visitedJunctions[0] = true;
		bool SpanningTreeCompleted = false;


		while(!SpanningTreeCompleted){//calcula o custo da árvore geradora mínima

			SpanningTreeCompleted = true;

			int chosen;
			int chosenLenght = 200001;

			//procura entre todas as arestes
			for(i = 0; i < n; i++){
			//uma aresta que esteja ligada a árvore e outra que esteja livre e que tenha tamanho mínimo
				if((visitedJunctions[roads[i][0]]) && (!visitedJunctions[roads[i][1]]) && (roads[i][2] < chosenLenght)){
					SpanningTreeCompleted = false;
					chosen = roads[i][1];
					chosenLenght = roads[i][2];
				}
				else if((visitedJunctions[roads[i][1]]) && (!visitedJunctions[roads[i][0]]) && (roads[i][2] < chosenLenght)){
					SpanningTreeCompleted = false;
					chosen = roads[i][0];
					chosenLenght = roads[i][2];
				}
			}

			if(chosenLenght < 200001){
				minimumSpanningTreeCost += chosenLenght;
				visitedJunctions[chosen] = true;
			}
		}

		cout << (totalCost - minimumSpanningTreeCost) << endl;

		cin >> m >> n;
	}

	return(0);
}
