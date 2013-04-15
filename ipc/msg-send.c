#include <string.h>
#include <sys/msg.h>

#define NUM_MSG 135000000

int main() {

  int i = 0;
  int msqid = 65536;
  struct message {
    long type;
    char text[20];
  } msg;


  msg.type = 1;
  strcpy(msg.text, "This is message 1");

  for (i = 0; i < NUM_MSG; i++)
    msgsnd(msqid, (void *) &msg, sizeof(msg.text), IPC_NOWAIT);

  return 0;
}
