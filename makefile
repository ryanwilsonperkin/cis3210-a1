CC = gcc
CFLAGS = -Wall -std=c99

all: n1 n2 n3 n4 n5 n6 n7

n1: node.o packet.o n1.c
	$(CC) $(CFLAGS) node.o packet.o n1.c -o n1

n2: node.o packet.o n2.c
	$(CC) $(CFLAGS) node.o packet.o n2.c -o n2

n3: node.o packet.o n3.c
	$(CC) $(CFLAGS) node.o packet.o n3.c -o n3

n4: node.o packet.o n4.c
	$(CC) $(CFLAGS) node.o packet.o n4.c -o n4

n5: node.o packet.o n5.c
	$(CC) $(CFLAGS) node.o packet.o n5.c -o n5

n6: node.o packet.o n6.c
	$(CC) $(CFLAGS) node.o packet.o n6.c -o n6

n7: node.o packet.o n7.c
	$(CC) $(CFLAGS) node.o packet.o n7.c -o n7

packet.o: packet.c
	$(CC) $(CFLAGS) -c packet.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

clean:
	rm *.o
