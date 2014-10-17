#include <stdio.h>
#include <unistd.h>

#include "packet.h"

#define PARENT_NODE     1
#define THIS_NODE       2
#define NUM_CHILDREN    1

int get_child_index(int child_node)
{
    switch (child_node) {
        case 4: return 0;
        default: return -1;
    }
}

int main(int argc, char *argv[])
{
    int read_parent, write_child[NUM_CHILDREN];
    packet p;

    read_parent = get_link(PARENT_NODE, THIS_NODE, READ);
    write_child[get_child_index(4)] = get_link(THIS_NODE, 4, WRITE);
    fprintf(stderr, "read_parent: %d, write_child[0]: %d\n", read_parent, write_child[0]);fflush(stderr);
    while (1) {
        recv_packet(read_parent, &p);
        if (p.dest == THIS_NODE) {
            if (p.data == END_OF_TEXT) {
                close(read_parent);
                acknowledge(THIS_NODE, PARENT_NODE);
                read_parent = get_link(THIS_NODE, PARENT_NODE, READ);
            } else if (p.data == END_OF_TRANSMISSION) {
                close(read_parent);
                acknowledge(THIS_NODE, PARENT_NODE);
                return 0;
            } else {
                printf("%c", p.data);
                fflush(stdout);
            }
        } else {
            send_packet(write_child[get_child_index(p.dest)], p);
            if (p.data == END_OF_TEXT || p.data == END_OF_TRANSMISSION) {
                close(write_child[get_child_index(p.dest)]);
                recv_acknowledge(p.dest, THIS_NODE);
                acknowledge(THIS_NODE, PARENT_NODE);
            }
            if (p.data == END_OF_TEXT) {
                write_child[get_child_index(p.dest)] = get_link(THIS_NODE, p.dest, WRITE);
            }
        }
    }
}
