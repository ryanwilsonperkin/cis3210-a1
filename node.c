#include <stdio.h>
#include <unistd.h>

#include "node.h"
#include "packet.h"

int get_child_index(int value, int num_children, int children[static MAX_CHILDREN])
{
    for (int i = 0; i < num_children; i++) {
        if (value == children[i]) {
            return i;
        }
    }
    return -1;
}

int branch_node(int this_node, int parent_node, int num_children, int children[MAX_CHILDREN])
{
    int child_index;
    int read_parent, write_child[MAX_CHILDREN];
    packet p;

    // Initialize read and write pipes for parent and children.
    read_parent = get_link(parent_node, this_node, READ);
    for (int i = 0; i < num_children; i++) {
        write_child[i] = get_link(this_node, children[i], WRITE);
    }

    // Loop until END_OF_TRANSMISSION message received.
    while (1) {

        // Receive packet from parent node.
        recv_packet(read_parent, &p);

        // Check if packet is destined for this node.
        if (p.dest == this_node) {

            // Send acknowledge message in response to end of text for file being printed.
            if (p.data == END_OF_TEXT) {
                close(read_parent);
                send_acknowledge(this_node, parent_node);
                read_parent = get_link(this_node, parent_node, READ);

            // Send acknowledge message in response to being told to quit, then quit.
            } else if (p.data == END_OF_TRANSMISSION) {
                close(read_parent);
                send_acknowledge(this_node, parent_node);
                return 0;

            // If not a special message, then print the data to stdout.
            } else {
                printf("%c", p.data);
                fflush(stdout);
            }

        // If packet is not destined for this node, then it is for a child.
        } else {
            child_index = get_child_index(p.dest, num_children, children);

            // Re-route the packet to the child.
            send_packet(write_child[child_index], p);

            // Re-route acknowledge messages from child node.
            if (p.data == END_OF_TEXT || p.data == END_OF_TRANSMISSION) {
                close(read_parent);
                close(write_child[child_index]);
                recv_acknowledge(p.dest, this_node);
                send_acknowledge(this_node, parent_node);
                read_parent = get_link(parent_node, this_node, READ);
            }
            if (p.data == END_OF_TEXT) {
                write_child[child_index] = get_link(this_node, p.dest, WRITE);
            }
        }
    }
}

int leaf_node(int this_node, int parent_node)
{
    int read_parent;
    packet p;

    // Initialize read pipe for parent.
    read_parent = get_link(this_node, parent_node, READ);

    // Loop until END_OF_TRANSMISSION message received.
    while (1) {

        // Receive packet from parent node.
        recv_packet(read_parent, &p);

        // Send acknowledge message in response to end of text for file being printed.
        if (p.data == END_OF_TEXT) {
            close(read_parent);
            send_acknowledge(this_node, parent_node);
            read_parent = get_link(this_node, parent_node, READ);

        // Send acknowledge message in response to being told to quit, then quit.
        } else if (p.data == END_OF_TRANSMISSION) {
            close(read_parent);
            send_acknowledge(this_node, parent_node);
            return 0;

        // If not a special message, then print the data to stdout.
        } else {
            printf("%c", p.data);
            fflush(stdout);
        }
    }
}
