#include <stdio.h>
#include <stdlib.h>
#define MAX 10
int id1, id2;

void filho(int n) {
	int i;
	for(i = 0; i < MAX; ++i)
		printf("Filho%d ",n);
	exit(0);
}

int main() {
	int i;
	
	if((id1 = fork()) == 0) 
		filho(1);
	if((id2 = fork()) == 0) 
		filho(2);
	if((id2 = fork()) == 0) 
		filho(3);

	for(i = 0; i < MAX; ++i)
		printf("Pai ");
	exit(0);
}
	
