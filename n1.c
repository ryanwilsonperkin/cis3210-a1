#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
void get_user_input(char **filename, char *nodename)
{
    char filename_buffer[MAX_BUF_SIZE] = {'\0'}, nodename_buffer[MAX_BUF_SIZE] = {'\0'};
    do {
        printf("Enter a file name and destination node: ");
        scanf(" %s %s", filename_buffer, nodename_buffer);

        if (!(nodename_buffer[1] >= '1' && nodename_buffer[1] <= '6')) {
            fprintf(stderr, "error: %s is not a valid destination node.\n", nodename_buffer);
        }
        if (access(filename_buffer, R_OK) == -1) {
            fprintf(stderr, "error: could not read from %s\n", filename_buffer);
        }
    } while (!(nodename_buffer[1] >= '2' && nodename_buffer[1] <= '7') || access(filename_buffer, R_OK) == -1);

    *filename = malloc(strlen(filename_buffer));
    *filename = strcpy(*filename, filename_buffer);
    *nodename = nodename_buffer[1];
}

int main(int argc, char *argv[])
{
    return 0;
}
