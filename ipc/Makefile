
CFLAGS= -g  

all: msg-send msg-recv

msg-send: msg-send.c
	gcc -o msg-send msg-send.c $(CFLAGS)

msg-recv: msg-recv.c 
	gcc -o msg-recv msg-recv.c $(CFLAGS) 

clean:
	rm -rf msg-recv msg-send
