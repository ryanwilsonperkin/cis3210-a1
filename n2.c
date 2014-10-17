#include <stdio.h>
#include <unistd.h>

#include "packet.h"

#define PARENT_NODE 1
#define THIS_NODE 2

int main(int argc, char *argv[])
{
    int read_parent;
    int quit;
    packet p;

    quit = 0;
    read_parent = get_link(THIS_NODE, PARENT_NODE, READ);
    do {
        recv_packet(read_parent, &p);
        if (p.dest == 2) {
            if (p.data == END_OF_TEXT) {
                close(read_parent);
                acknowledge(PARENT_NODE, THIS_NODE);
                read_parent = get_link(THIS_NODE, PARENT_NODE, READ);
            } else if (p.data == END_OF_TRANSMISSION) {
                close(read_parent);
                acknowledge(PARENT_NODE, THIS_NODE);
                quit = 1;
            } else {
                printf("%c", p.data);
                fflush(stdout);
            }
        } else if (p.dest == 4) {
        }
    } while (!quit);
}
