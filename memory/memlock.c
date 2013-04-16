#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/mman.h>


#define X 1024*1024*1024

void main(void) {

	void *d;

	d = malloc(X ); 

	printf("Value of d is %ld\n", d);	

	mlock(d, X); 
        // memset(d, 3, X );

	while(1){ }



}
