#define _GNU_SOURCE
#include <time.h> 
#include <sys/times.h> 

#include <stdio.h> 
#include <limits.h> 
#include <sys/time.h>
#include <unistd.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <dlfcn.h>



clock_t times (struct tms *buffer)
{

  clock_t (*orig_times)(struct tms*) = dlsym(RTLD_NEXT, "times");

  clock_t clk_tck;
  time_t _posix_start_time;

  _posix_start_time = time ((time_t *) NULL);
  clk_tck = sysconf(_SC_CLK_TCK);

  static int x = -10; 

  clock_t t = orig_times(buffer); 
  buffer->tms_utime = (clock_t) LONG_MAX - x;
  buffer->tms_stime = (clock_t) LONG_MAX - x;

  buffer->tms_cutime = (clock_t) LONG_MAX -x ;
  buffer->tms_cstime = (clock_t) LONG_MAX -x ; 

  return (time ((time_t *) NULL) - _posix_start_time) * clk_tck;



}

