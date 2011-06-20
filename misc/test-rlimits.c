#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

int main (int argc, char** argv) {
 struct rlimit before_limit, set_limit, after_limit;
 int ret;
 getrlimit(RLIMIT_NOFILE,&before_limit);
 printf("current: %u   max %u\n",before_limit.rlim_cur,before_limit.rlim_max\
);

 printf("trying to set infinity\n");
 set_limit.rlim_cur = RLIM_INFINITY;
 set_limit.rlim_max = RLIM_INFINITY;
 if (ret = setrlimit(RLIMIT_NOFILE,&set_limit)) {
   perror("setrlimit error:");
 }

 printf("trying to set 2048\n");
 set_limit.rlim_cur = 2048;
 set_limit.rlim_max = 2048;
 if (ret = setrlimit(RLIMIT_NOFILE,&set_limit)) {
   perror("setrlimit error:");
 }


 getrlimit(RLIMIT_NOFILE,&after_limit);
 printf("current: %u   max %u\n",after_limit.rlim_cur,after_limit.rlim_max);
}

