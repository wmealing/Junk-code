#include <stdio.h>
#include <math.h>
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define REMOTEHOST "localhost" // remote server we are testing.  
#define PORT "9999" // the port client will be connecting to 

#define MAXDATASIZE 100 // max number of bytes we can get at once 

#define CPUCOUNT 4
#define THREADCOUNT 130


// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


int connect_and_wait() {
    

    int sockfd, numbytes;
    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];


    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo( REMOTEHOST , PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
    }

    sleep(9999);



}

void *thread_func(void *param) 
{
    long current_cpu = (long) param; 
	
    if (pthread_setaffinity_np(pthread_self(), sizeof(current_cpu), &current_cpu) <0) {
        perror("pthread_setaffinity_np");
    }


   connect_and_wait(); 

}
int main(int argc, char *argv[])
{

    long t = 1;
    int x = 1;

    pthread_t thread[THREADCOUNT];

    	for ( x = 0; x < THREADCOUNT ; x++) {
		t++;
		if (pthread_create(&thread[x], NULL, thread_func, (void*)t) != 0) 	{
      			  perror("pthread_create");
   		}
	
		if (t >= 3) {
			 t = 0;
		}
	}
    pthread_exit(NULL);
}

