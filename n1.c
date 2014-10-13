#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char *argv[])
{
    return 0;
}
