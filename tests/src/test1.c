#include <stdlib.h>
#include <memtrack_05.h>
int main(void){
	char *a=malloc(1);
	char *b=malloc(1);
	char *c = calloc(1,sizeof(char));
	a = realloc(a,sizeof(char));
	free(a);
	b++;
	free(b); // Erreur free
	free(c);
	return 0;
}