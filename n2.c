#include <stdio.h>
#include <unistd.h>

#include "packet.h"

int main(int argc, char *argv[])
{
    int link, quit;
    packet p;

    quit = 0;
    do {
        link = get_link(2, 1);
        recv_packet(link, &p);
        close(link);
        if (p.dest == 2) {
            if (p.data == END_OF_TEXT) {
                p.dest = 1;
                p.data = ACKNOWLEDGE;
                link = get_link(1, 2);
                send_packet(link, p);
                close(link);
            } else if (p.data == END_OF_TRANSMISSION) {
                p.dest = 1;
                p.data = ACKNOWLEDGE;
                link = get_link(1, 2);
                send_packet(link, p);
                close(link);
                quit = 1;
            } else {
                printf("%c", p.data);
            }
        } else if (p.dest == 4) {
            link = get_link(2, 4);
            send_packet(link, p);
            close(link);
            if (p.data == END_OF_TEXT || p.data == END_OF_TRANSMISSION) {
                link = get_link(1, 2);
                send_packet(link, p);
                close(link);
            }
        }
    } while (!quit);
}
