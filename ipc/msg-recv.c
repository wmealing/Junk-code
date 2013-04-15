#include <stdio.h>
#include <sys/msg.h>
#include <errno.h>


#define NUM_MSG 135000000

int main() {

  int i = 0;
  int msqid = 65536;
  struct message {
    long type;
    char text[20];
  } msg;

  long msgtyp = 0;

  for(i = 0; i < NUM_MSG; i++) {
	if (msgrcv(msqid, (void *) &msg, sizeof(msg.text), msgtyp, MSG_NOERROR) == 0) {
		printf(".");
	}
	else {
      printf("ERROR: %s\n", strerror(errno));
	}
  }

  return 0;
}
