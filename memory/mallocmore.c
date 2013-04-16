#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 

int main(void) {

	int x;

	char *rubbish;

	while (1) {
		rubbish = malloc(x  * 10);
		usleep(1);
		free(rubbish); 
		x++;
	}
	

}
