#include <stdlib.h>
int main(void){
	char *a=malloc(1);
	char *b=malloc(1);
	free(a);
	b++;
	free(b);
	return 0;
}