#include <fcntl.h>
#include <unistd.h>

#include "packet.h"

int send_packet(int destination_fd, packet p)
{
    char buffer[2] = {p.dest, p.data};
    int result = write(destination_fd, buffer, 2);
    return result;
}

int recv_packet(int source_fd, packet *p)
{
    char buffer[2] = {0, 0};
    int result = read(source_fd, buffer, 2);
    p->dest = buffer[0];
    p->data = buffer[1];
    return result;
}

int get_link(int source, int dest)
{
    int oflag;
    char link_name[6] = "link\0\0";
    char link_map[7][7] = {
        {'0', '1', '2', '1', '2', '2', '2'},
        {'1', '0', '0', '3', '0', '0', '0'},
        {'2', '0', '0', '0', '4', '5', '6'},
        {'1', '3', '0', '0', '0', '0', '0'},
        {'2', '0', '4', '0', '0', '0', '0'},
        {'2', '0', '5', '0', '0', '0', '0'},
        {'2', '0', '6', '0', '0', '0', '0'},
    };

    link_name[4] = link_map[source - 1][dest - 1];
    oflag = (source < dest) ? O_WRONLY : O_RDONLY;
    return open(link_name, oflag);
}
