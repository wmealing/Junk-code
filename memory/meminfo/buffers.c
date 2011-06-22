#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/mman.h>
#include <ncurses.h> 


#define MALLOC_SIZE 1024
#define READ_COUNT 1024 * 1024  

#define DEVICE "/dev/sda"

#define FILL '\0'
/*
 * Testing the /proc/meminfo "buffers" value.
 * 
 * Defined as: Relatively temporary storage for raw disk blocks
 * shouldn't get tremendously large (20MB or so)
 */


int main(void) {

	FILE *fp;
	void *buf;
	int count = 0;

	size_t bytes_read = 0;

	if ((fp = fopen(DEVICE, "r")) == NULL)
        	return;

	buf = malloc(MALLOC_SIZE); 

	for( count = 0; count <= READ_COUNT; count++) {	
		bytes_read += fread(buf, 1, MALLOC_SIZE, fp);
	}

	printf("%d Mbytes read, press any key to continue\n" , bytes_read / 1024 / 1024 );



	free(buf);
	fclose(fp);



}
