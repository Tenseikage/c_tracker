#include <stdlib.h>
#include <memtrack_05.h>
int main(void){
	//Code fonctionnel
	char *a=malloc(1);
	char *b=malloc(1);
	char *c = calloc(1,sizeof(char));
	free(a);
	a = realloc(a,1);
	free(b); 
	free(c);
	return 0;
}