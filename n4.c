#include <stdio.h>
#include <unistd.h>

#include "packet.h"

#define PARENT_NODE     2
#define THIS_NODE       4

int main(int argc, char *argv[])
{
    int read_parent;
    packet p;

    read_parent = get_link(THIS_NODE, PARENT_NODE, READ);
    while (1) {
        recv_packet(read_parent, &p);
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
    }
}
