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
