#include <stdlib.h>
#include <memtrack_05.h>
int main(void){
	char *a=malloc(1);
	char *b=malloc(1);
	char* d;
	char *c = calloc(1,sizeof(char));
	a = realloc(a,sizeof(char));
	free(a);
	free(b); 
	free(c);
	free(d);// Erreur free
	return 0;
}