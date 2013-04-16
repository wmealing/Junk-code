#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define CPUCOUNT 16

double waste_time(long n)
{
    double res = 0;
    long i = 0;
    while (i <n * 200000) {
        i++;
        res += sqrt(i);
    }
    return res;
}

void *thread_func(void *param) 
{
	long current_cpu = (long) param; 
	
    if (pthread_setaffinity_np(pthread_self(), sizeof(current_cpu), &current_cpu) <0) {
        perror("pthread_setaffinity_np");
    }
    printf("result: %f\n", waste_time(2000));
}
int main(int argc, char *argv[])
{

    long t = 1;
    int x = 1;

    pthread_t thread[CPUCOUNT];

    	for ( x = 0; x < CPUCOUNT ; x++) {
		t++;
		if (pthread_create(&thread[x], NULL, thread_func, (void*)t) != 0) 	{
      			  perror("pthread_create");
   		}
	}
    pthread_exit(NULL);
}

