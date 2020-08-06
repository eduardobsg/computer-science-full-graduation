#include <iostream>
#include <stdlib.h>

using namespace std;

class VetorInteiros {
	
	public:
		int tamanho;
		int* dados;    
		
		VetorInteiros(int t) {
			tamanho = t;
			dados = new int[tamanho];
		}    
		
		~VetorInteiros() {
			delete[] dados;
		}
		
		VetorInteiros& operator=(const VetorInteiros &v) {
			if(this.tamanho == v.tamanho) {
				for(int i = 0; i < v.tamanho; i++) {
					this.dados[i] = v.dados[i];
				}					
			}
			return *this;
		}
};

int main(void) {
   
	VetorInteiros v(10); // cria um vetor para 10 inteiros
	v.dados[0] = 1;
	
	{
		VetorInteiros c(10);
		cout << "Conteudo original:" << v.dados[0] << std::endl;
		//cout << "Conteudo na copia:" << c.dados[0] << std::endl;
	} 

	cout << "Conteudo original:" << v.dados[0] << std::endl;

	return 0;
}
