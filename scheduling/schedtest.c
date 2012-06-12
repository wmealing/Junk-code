/* -------------------------------------------------------------------------
*  timing_test.c
*
*  gcc -m32 -g -O3 -lm -o outputbinary thislfile.c
   gcc -m64 -g -O3 -lm -o outputbinary thisfile.c 
*
*  Based on agua_frag_test
*  Version 4
------------------------------------------------------------------------- */

#include <math.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>

/* Stop after KLOOPS * 1000 iterations */
#define KLOOPS              10

/* YOU WILL NEED TO MODIFY THESE */ 
#define TEST_MIN_TIME_MAX 100 /* miliseconds - sanity check */
#define TEST_AVG_TIME_MAX 500 /* miliseconds - sanity check */
#define TEST_MAX_TIME_MAX 1000 /* miliseconds - sanity check */
#define TEST_STD_DEV_MAX 11


/*-------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int    loop_iter=0;
    time_t time_n;
    struct timeval tm_start,tm_end;
    unsigned times[KLOOPS * 1000];
    long     total_time=0;
    long     minimum_time=0xFFFFFF;
    long     maximum_time=0;
    float    mean_time=0;
    float    standard_deviation=0;

    /* This is the test to run for KLOOPS loops */
    for (loop_iter=0;(loop_iter/1000)<KLOOPS;loop_iter++)
    {
            gettimeofday(&tm_start,NULL);

            while (1) {
		// INSERT WORK HERE WITH BREAK CONDITION.
                break;
            }
            gettimeofday(&tm_end,NULL);
            time_n = ((tm_end.tv_sec * 1000000L)+tm_end.tv_usec)-((tm_start.tv_sec*1000000L)+tm_start.tv_usec);

	   /*
            * Store timings for each iteration to calculate std. dev
            * and also keep track of minimum and maximum times
            * incase they're useful later
            */

            times[loop_iter] = time_n/1000;
            total_time += times[loop_iter];

            if (times[loop_iter] < minimum_time)
                minimum_time = times[loop_iter];

            if (times[loop_iter] > maximum_time)
                maximum_time = times[loop_iter];
           
            if ((loop_iter % 1000) == 0)
	            fprintf(stderr,".");
    }

    mean_time = total_time / (KLOOPS * 1000);

    for(loop_iter=0;loop_iter < (KLOOPS * 1000);loop_iter++)
        standard_deviation += (times[loop_iter] - mean_time) * 
                   (times[loop_iter] - mean_time);

    standard_deviation = sqrtf( standard_deviation / (KLOOPS * 1000) );

    printf("\n\nMin Time (ms): %ld\n",minimum_time);
    printf("Avg. Time (ms): %0.4f\n", mean_time);
    printf("Max Time (ms): %ld\n", maximum_time);
    printf("Std Dev (ms): %0.4f\n",standard_deviation);

    /* report results as exit code */
    if ( (minimum_time > TEST_MIN_TIME_MAX) || (mean_time > TEST_AVG_TIME_MAX) ||
                                           (maximum_time > TEST_MAX_TIME_MAX) ) {
	    printf("Min/Max/Avg times are outside window.\n");
        return 2;

    } else if (standard_deviation > TEST_STD_DEV_MAX) {
        printf("Standard deviation exceeds %d\n", TEST_STD_DEV_MAX);
    	return 3;
    }

    return 0;
}
