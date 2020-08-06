// Colour Hash （色彩缤纷游戏）  
// PC/UVa IDs: 110807/704, Popularity: B, Success rate: average Level: 3  
// Verdict: Accepted  
// Submission Date: 2011-08-28  
// UVa Run Time: 0.048s  

// Estado mais facilmente TLE, de modo que o uso de duas vias de pesquisa abordagem de busca, inverso: busca unidirecional de um determinado estado de o estado de destino  
// Procura Passo 8, para gravar todos os resultados obtidos no conjunto A; pesquisa direta: Pesquisa Passo 9, a partir de um dado estado é gerado no processo de busca  
// Um estado no conjunto A, que pode encontrar uma solução em 16 passos, ou não pode encontrar a solução.  
// Este é o mais crítico para a forma de representar o estado atual do jogo, a fim de evitar a adição de estado duplicado no conjunto A, pode usar uma corda para representar  
// O estado atual do controle deslizante. O conjunto A Você pode usar o mapa para determinar se o estado duplicado.  

#include <iostream>
#include <queue>
#include <map>

using namespace std;

#define LEFT_CLOCKWISE 1 //a esquerda, no sentido horário.  
#define RIGHT_CLOCKWISE 2 //lateral direita no sentido horário.  
#define LEFT_COUNTERCLOCKWISE 3 //a esquerda anti-horário.  
#define RIGHT_COUNTERCLOCKWISE 4 //lateral direita esquerda.  

#define NWHEEL 24		//para o número total.  
#define HALF_WHEEL 9		//número do lado esquerdo da barra.
#define MIDDLE_WHEEL 3		//do controle deslizante do meio.  
#define BACKWARD_DEPTH 8	//profundidade de pesquisa Reverse.  

//Estado Target. Armazenamento deixado deslizante - ao lado direito da barra - o meio da barra, porque o número 10 deslizante representaram dois caracteres, então com 10 Britânica  
//Letra T Primeiro em (10).  
string target = "034305650078709T90121";

//Cache pesquisa inversa, usar a corda para representar o estado ea seqüência de rotação. 
map < string, string > cache;

//Operação do inverso da rotação. Um inverso do inverso de 3,2 a 4, e assim por diante. 
int reverse[4] = { 3, 4, 1, 2 };

//Representa o controle deslizante estrutura do estado atual.  
struct node {
	string config;		//o controle deslizante Estado.  
	string sequences;	//seqüência/rotação para chegar a esta posição. 
};

//Especifique a direção do controle deslizante de rotação.。
void rotate(string &config, int direction) {

	//Pega o meio da parte deslizante.  
	string middle = config.substr(HALF_WHEEL * 2);

	switch(direction) {
		//Rotação no sentido horário do lado esquerdo da barra.  
		case LEFT_CLOCKWISE:

			config[HALF_WHEEL * 2] = config[HALF_WHEEL - 2];
			config[HALF_WHEEL * 2 + 1] = config[HALF_WHEEL - 1];
			config[HALF_WHEEL * 2 + 2] = middle[0];

			for (int i = HALF_WHEEL - 1; i >= 2; i--)
				config[i] = config[i - 2];
			config[1] = middle[2];
			config[0] = middle[1];

			break;

		//Controle deslizante direito rotação no sentido horário. 
		case RIGHT_CLOCKWISE:

			config[HALF_WHEEL * 2] = middle[2];
			config[HALF_WHEEL * 2 + 1] = config[HALF_WHEEL];
			config[HALF_WHEEL * 2 + 2] = config[HALF_WHEEL + 1];

			for (int i = HALF_WHEEL; i <= (HALF_WHEEL * 2 - 3); i++)
				config[i] = config[i + 2];
			config[HALF_WHEEL * 2 - 2] = middle[0];
			config[HALF_WHEEL * 2 - 1] = middle[1];

			break;

		//Anti-horário de rotação do lado esquerdo da barra.
		case LEFT_COUNTERCLOCKWISE:

			config[HALF_WHEEL * 2] = middle[2];
			config[HALF_WHEEL * 2 + 1] = config[0];
			config[HALF_WHEEL * 2 + 2] = config[1];

			for (int i = 0; i <= HALF_WHEEL - 3; i++)
				config[i] = config[i + 2];
			config[HALF_WHEEL - 2] = middle[0];
			config[HALF_WHEEL - 1] = middle[1];

			break;

		//Controle deslizante direito rotação anti-horária.  
		case RIGHT_COUNTERCLOCKWISE:

			config[HALF_WHEEL * 2] = config[HALF_WHEEL * 2 - 2];
			config[HALF_WHEEL * 2 + 1] = config[HALF_WHEEL * 2 - 1];
			config[HALF_WHEEL * 2 + 2] = middle[0];

			for (int i = 2 * HALF_WHEEL - 1; i >= HALF_WHEEL + 2; i--)
				config[i] = config[i - 2];
			config[HALF_WHEEL + 1] = middle[2];
			config[HALF_WHEEL] = middle[1];

			break;
	}
}

// Gerados a partir do estado de destino de todos os estados possíveis produzida no passo 8, um método de utilização de uma largura de busca em primeiro lugar, com o mapa do estado armazenada a geração e a correspondente  
// Rotação / sequência. 
void backward_search(string config) {
	queue <node> open;

	node tmp;
	tmp.config = config;
	tmp.sequences = "";

	open.push(tmp);

	while(!open.empty()) {
		node copy = open.front();
		open.pop();

		//Parar quando estendida até uma profundidade de 8 camadas continuam a expandir-se, neste estado.  
		if(copy.sequences.length() >= BACKWARD_DEPTH)
			continue;

		for(int i = LEFT_CLOCKWISE; i <= RIGHT_COUNTERCLOCKWISE; i++) {
			//Ir inválido móvel, no passo anterior, por exemplo, utilizando uma rotação no sentido horário do lado esquerdo, em seguida, a corrente If usando  
            //Esquerda rotação anti-horária vai voltar ao passo anterior.  
			if(copy.sequences.length() > 0) {
				//Note o uso de a operação de rotação inversa, é necessário para restaurar o juiz.  
				int last_rotate = reverse[copy.sequences[0] - '0' - 1];
				if(last_rotate != i && ((last_rotate + i) == 4 || (last_rotate + i) == 6))
					continue;
			}

			string t = copy.config;
			rotate(t, i);

			if(cache.find(t) == cache.end()) {
				node successor;
				successor.config = t;
				//Record em sequência de rotação reversa, utilizando o inverso da rotação actual.  
				successor.sequences = (char)('0' + reverse[i - 1]) + copy.sequences;
				open.push(successor);

				cache.insert(make_pair<string, string>(t, successor.sequences));
			}
		}
	}
}

//Modo de busca em largura. 
bool forward_search(string config) {
	queue <node> open;

	node tmp;
	tmp.config = config;
	tmp.sequences = "";

	open.push(tmp);

	while(!open.empty()) {
		node copy = open.front();
		open.pop();

		//Foi encontrado no estado de cache, e saída a seqüência de rotação. 
		if(cache.find(copy.config) != cache.end()) {
			cout << copy.sequences;
			map <string, string>::iterator it = cache.find(copy.config);
			cout << (*it).second << endl;

			return true;
		}

		//Profundidade de pesquisa é 9.  
		if(copy.sequences.length() >= (BACKWARD_DEPTH + 1))
			continue;
			
		for(int i = LEFT_CLOCKWISE; i <= RIGHT_COUNTERCLOCKWISE; i++) {
			//Ir, antes e depois dos dois passos constituem o estado complementar.  
			if(copy.sequences.length() > 0) {
				int size = copy.sequences.length();
				int last_rotate = copy.sequences[size - 1] - '0';
				if(last_rotate != i && ((last_rotate + i) == 4 || (last_rotate + i) == 6))
					continue;
			}

			string t = copy.config;
			rotate(t, i);

			node successor;
			successor.config = t;
			successor.sequences = copy.sequences + (char)('0' + i);

			open.push(successor);
		}
	}

	return false;
}

//E do estado do alvo, determinar se o estado de resolver.  
bool solved(string config) {
	for(int i = 0; i < target.length(); i++)
		if(config[i] != target[i])
			return false;

	return true;
}

int main(int ac, char *av[]) {
	string config;
	int c;
	int cases;
	
	//os resultados da pesquisa reversa para referência futura. 
	backward_search(target);
	
	cin >> cases;
	while(cases--) {
		//Ler o estado inicial.  
		config.clear();
		for(int i = 0; i < NWHEEL; i++) {
			cin >> c;
			if(c == 10)
				config.append(1, 'T');
			else
				config.append(1, c + '0');
		}

		//Ajustes de representação.
		config = config.substr(0, HALF_WHEEL) +
			config.substr(HALF_WHEEL + MIDDLE_WHEEL, HALF_WHEEL) +
			config.substr(2 * HALF_WHEEL + MIDDLE_WHEEL);
		
		//Primeiro determinar se ele tem que resolver a situação.
		if (solved(config)) {
			cout << "PUZZLE ALREADY SOLVED" << endl;
			continue;
		}

		//Procura para a frente Localizar.  
		if (!forward_search(config))
			cout << "NO SOLUTION WAS FOUND IN 16 STEPS" << endl;
	}

	return 0;
}
