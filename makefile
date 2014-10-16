CC = gcc
CFLAGS = -Wall

all: n1 n2 n3 n4 n5 n6 n7

n1: packet.o n1.c
	$(CC) $(CFLAGS) packet.o n1.c -o n1

n2: packet.o n2.c
	$(CC) $(CFLAGS) packet.o n2.c -o n2

n3: packet.o n3.c
	$(CC) $(CFLAGS) packet.o n3.c -o n3

n4: packet.o n4.c
	$(CC) $(CFLAGS) packet.o n4.c -o n4

n5: packet.o n5.c
	$(CC) $(CFLAGS) packet.o n5.c -o n5

n6: packet.o n6.c
	$(CC) $(CFLAGS) packet.o n6.c -o n6

n7: packet.o n7.c
	$(CC) $(CFLAGS) packet.o n7.c -o n7

packet.o: packet.c
	$(CC) $(CFLAGS) -c packet.c

clean:
	rm *.o
