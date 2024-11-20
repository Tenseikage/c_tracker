#include <stdlib.h>
#include "mtrack_03.h"

int main(void){
  char *a=my_malloc(1);
	char *b=my_malloc(1);
	my_free(a);
	b++;
	my_free(b);
	return 0;
}