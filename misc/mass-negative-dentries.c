#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#define MAXDIR 1024 
#define MAXFILES 32000

int main(void) {

	int i,j;
	int size = 100; /* shouldn't need more than 100 bytes"  */ 

	char *d;
        struct stat discardme; 


	if ((d = malloc(size)) == NULL)
		exit(-1);

	for (i = 0; i < MAXDIR; i++) {
		for (j = 0 ; j < MAXFILES; j++) {
			*d = NULL; 
			sprintf(d, "/tmp/%d/%d", i, j);
			printf("Statting /tmp/%d/%d\n", i, j); 
			stat(d, &discardme); 
		}
	}

	free(d); 

return 0;

}
