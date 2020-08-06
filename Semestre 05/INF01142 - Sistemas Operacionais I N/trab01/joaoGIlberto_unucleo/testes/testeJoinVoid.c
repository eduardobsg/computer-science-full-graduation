#include "../include/libsisop.h"

void f(void) {}

int main() {
	libsisop_init();
	int r = mproc_join( mproc_create(f, NULL) );
	printf("return join void: %d\n", r);
	return 0;
}
