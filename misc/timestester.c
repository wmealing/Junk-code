#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <sys/times.h>
#include <limits.h> 
#include <sys/resource.h>
#include <errno.h> 

#define TICKS_PER_SEC sysconf(_SC_CLK_TCK)



int main(void) {


	printf("Starting overflow example"); 
	
	struct tms *t;
	clock_t c; 

	t = malloc(sizeof(struct tms)); 


	while(1) {
		c = times(t);
		printf ("times returned: %.2f\n",(double) (c + 0.0) / TICKS_PER_SEC);
	}
	

	free(t); 

return 1; 
}
