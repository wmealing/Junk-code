#include <stdio.h>
#include <sys/msg.h>
#include <errno.h>


#define NUM_MSG 135000000

int main() {

  int i = 0;
  int ret = 0;
  int msqid = 65536;
  struct message {
    long type;
    char text[20];
  } msg;

  long msgtype = 0;

  for(i = 0; i < NUM_MSG; i++) {
	ret = msgrcv(msqid, (void *) &msg, sizeof(msg.text), msgtype, MSG_NOERROR);

	if (errno) {
	      printf("ERROR: %s\n", strerror(errno));
	}
  }

  return 0;
}
