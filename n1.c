#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "packet.h"

#define MAX_BUF_SIZE 1024

/*
 * get_file_contents
 *  Retrieve contents of file into character buffer.
 *
 *  filename: name of file to read from
 *  contents: pointer to string to read characters into
 *
 *  returns: number of characters read into contents string
 */
long get_file_contents(char *filename, char **contents)
{
    long n_chars = 0;
    FILE *f = fopen(filename, "rb");

    if (f) {
        fseek(f, 0, SEEK_END);
        n_chars = ftell(f) / sizeof(char);
        fseek(f, 0, SEEK_SET);
        *contents = malloc(n_chars * sizeof(char));
        if (contents) {
            fread(*contents, sizeof(char), n_chars, f);
        }
    }
    return n_chars;
}

/*
 * get_user_input
 *  Gets user input about which filename to read from and destination node to write to.
 *
 *  filename: pointer to string to allocate and fill with file name
 *  nodename: pointer to character to assign to node name (one of '1' - '7')
 */
void get_user_input(char **filename, int *node)
{
    char filename_buffer[MAX_BUF_SIZE] = {'\0'};

    printf("Enter a file name and destination node: ");
    scanf(" %s n%d", filename_buffer, node);

    *filename = malloc(strlen(filename_buffer));
    *filename = strcpy(*filename, filename_buffer);
}

/*
 * should_quit
 *  Gets user input to decide whether to quit.
 *
 *  returns: 1 if program should quit, 0 otherwise
 */
int should_quit()
{
    char response = '\0';
    printf("Continue? (Y/N) ");
    scanf(" %c", &response);

    return (response == 'N') ? 1 : 0;
}

/*
 * send_data
 *  Send characters of data to a node.
 *
 *  node: the node to send the data to
 *  n_chars: the number of characters in the data
 *  data: the data to send to the node
 */
void send_data(int node, int n_chars, char *data)
{
    packet p;
    int link = get_link(1, node);

    p.dest = (char) node;
    for (int i = 0; i < n_chars; i++) {
        p.data = data[i];
        send_packet(link, p);
    }

    p.data = END_OF_TEXT;
    send_packet(link, p);
    close(link);
}

int main(int argc, char *argv[])
{
    char *filename, *contents;
    long n_chars;
    int link, node, quit;
    packet p;

    do {
        get_user_input(&filename, &node);
        n_chars = get_file_contents(filename, &contents);
        send_data(node, n_chars, contents);

        link = get_link(node, 1);
        recv_packet(link, &p);
        assert(p.data == ACKNOWLEDGE);
        close(link);

        quit = should_quit();
        if (quit) {
            p.data = END_OF_TRANSMISSION;
            for (int i = 1; i < 7; i++) {
                link = get_link(1, i);
                p.dest = (char) i;
                send_packet(node, p);
                close(link);

                link = get_link(i, 1);
                recv_packet(link, &p);
                assert(p.data == ACKNOWLEDGE);
                close(link);
            }
        }
        free(filename);
        free(contents);
    } while(!quit);
    return 0;
}
