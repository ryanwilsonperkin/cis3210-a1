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

    read_parent = get_link(parent_node, this_node, READ);
    for (int i = 0; i < num_children; i++) {
        write_child[i] = get_link(this_node, children[i], WRITE);
    }

    while (1) {
        recv_packet(read_parent, &p);
        if (p.dest == this_node) {
            if (p.data == END_OF_TEXT) {
                close(read_parent);
                acknowledge(this_node, parent_node);
                read_parent = get_link(this_node, parent_node, READ);
            } else if (p.data == END_OF_TRANSMISSION) {
                close(read_parent);
                acknowledge(this_node, parent_node);
                return 0;
            } else {
                printf("%c", p.data);
                fflush(stdout);
            }
        } else {
            child_index = get_child_index(p.dest, num_children, children);
            send_packet(write_child[child_index], p);
            if (p.data == END_OF_TEXT || p.data == END_OF_TRANSMISSION) {
                close(read_parent);
                close(write_child[child_index]);
                recv_acknowledge(p.dest, this_node);
                acknowledge(this_node, parent_node);
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

    read_parent = get_link(this_node, parent_node, READ);
    while (1) {
        recv_packet(read_parent, &p);
        if (p.data == END_OF_TEXT) {
            close(read_parent);
            acknowledge(this_node, parent_node);
            read_parent = get_link(this_node, parent_node, READ);
        } else if (p.data == END_OF_TRANSMISSION) {
            close(read_parent);
            acknowledge(this_node, parent_node);
            return 0;
        } else {
            printf("%c", p.data);
            fflush(stdout);
        }
    }
}
