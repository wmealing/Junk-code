#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/mman.h>


#define X 1024*1024*1024

/* This looks like it should allocate memory,
 * but it actually doesnt.
 *
 * Check the output of top / free while this spins madly.
 */

void main(void) {

	void *d;

	d = malloc(X ); 

	printf("Value of d is %ld\n", d);	


	while(1){ }

}
