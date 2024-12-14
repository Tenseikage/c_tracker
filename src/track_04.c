#include <stdlib.h>
int main(void){
	char *a=malloc(1);
	char *b=malloc(1);
	char *c = calloc(1,sizeof(char));
	a = realloc(a,sizeof(char));
	printf("ouiiioooooooo\n");
	free(a);
	b++;
	free(b);
	free(c);
	return 0;
}