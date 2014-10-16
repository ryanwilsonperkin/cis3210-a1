#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
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

int main(int argc, char *argv[])
{
    char *filename, *contents;
    long n_chars;
    int node, quit, write_fd, read_fd;
    packet p;

    do {
        get_user_input(&filename, &node);
        n_chars = get_file_contents(filename, &contents);
        write_fd = get_link(1, node);

        p.dest = (char)node;
        for (int i = 0; i < n_chars; i++) {
            p.data = contents[i];
            send_packet(write_fd, p);
        }
        p.data = '\0';
        send_packet(write_fd, p);
        close(write_fd);

        read_fd = get_link(node, 1);
        recv_packet(read_fd, &p);

        quit = should_quit();
        free(filename);
        free(contents);
    } while(!quit);
    return 0;
}
