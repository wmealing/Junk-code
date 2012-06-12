/* gcc -Wall -O2 -o pausetest pausetest.c */

#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <sched.h>

#define	PRIORITY	99
#define	MAX_PAUSE	10000

static uint64_t get_tsc() {
	unsigned a, d;
	asm volatile("rdtsc" : "=a" (a), "=d" (d));
	return ((uint64_t)a) | (((uint64_t)d) << 32);
}

int main(int argc, char** argv) {
	int i;						/* iterator for the loop */
	int rv;						/* return value */
	struct sched_param sp = { PRIORITY };		/* sched priority */

	uint64_t main_start;				/* when did the program start to run */

	uint64_t loop_start;
	uint64_t loop_end;
	uint64_t loop_elapsed;

	uint64_t foo;

	printf ("sched_setscheduler(): %d\n", sched_setscheduler (0, SCHED_FIFO, &sp));

	rv = mlockall (MCL_CURRENT | MCL_FUTURE);
	fprintf (stderr, "mlockall(): %d\n", rv);

	main_start = get_tsc();
	printf ("get_tsc(): %ld\n", main_start);

	while (1) {

		loop_start = get_tsc();
		foo = loop_start;

		for (i=0; i<1000; i++) {
			foo += (loop_start + i) ^ argc;
		}

		loop_end = get_tsc();
		loop_elapsed = loop_end - loop_start;

		/* this takes about 7700 cycles on a 2.66Ghz Xeon X5550 */
		if ( loop_elapsed > MAX_PAUSE ) {
			printf ("At %ld pause %ld is longer than %d\n", get_tsc(), loop_elapsed, MAX_PAUSE);
		}
	}
}
