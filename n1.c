#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "packet.h"

#define MAX_BUF_SIZE 1024
#define NUM_NODES 7

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
 *  node: pointer to integer to read number into
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

int main(int argc, char *argv[])
{
    char *filename, *contents;
    long n_chars;
    int write_child;
    int node;
    packet p;

    do {
        // Get filename and node number from user.
        get_user_input(&filename, &node);

        // Get contents of file.
        n_chars = get_file_contents(filename, &contents);

        // Send file data to node.
        send_data(1, node, n_chars, contents);

        // Receive acknowledgement packet from node.
        recv_acknowledge(1, node);

        free(filename);
        free(contents);
    } while (!should_quit());

    p.data = END_OF_TRANSMISSION;
    for (int i = NUM_NODES; i > 1; i--) {
        write_child = get_link(1, i, WRITE);
        p.dest = i;
        send_packet(write_child, p);
        close(write_child);

        recv_acknowledge(1, i);
    }
    return 0;
}
