/* Problema da mochila fracionaria
*/
#include <stdio.h>
#include <stdlib.h>

#define QTE_OBJS 6

int main() {
	int i;
	
	int custo[QTE_OBJS] = { 2, 5, 3, 20, 10, 1 }; //inicialização O(1)
	int peso[QTE_OBJS]	= { 5, 8, 1, 4, 7, 3 }; //inicialização O(1)

	float ratio[QTE_OBJS]; //custo por unidade de peso (custo/peso)
	float mochila[QTE_OBJS][2]; // [0]: 
	int pesoMochila = 12;	
		
	

	//Complexidade O(1) realizada n vezes => O(n)
	for(i = 0; i < QTE_OBJS; i++) 
		ratio[i] = (float) (custo[i] / peso[i]); //complexidade O(1)
		
	OrdenaRatio(ratio); //complexidade O(n)	
	
	
}
