#include <stdlib.h>
#include <memtrack_05.h>
int main(void){
	//Code fonctionnel
	char *a=malloc(1);
	char *b=malloc(1);
	char *c = calloc(1,sizeof(char));
	a = realloc(a,1);
	free(a);
	free(b); 
	free(c);
	return 0;
}