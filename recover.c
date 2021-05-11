#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BLOCK 512
typedef unsigned char BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    char *tfile = argv[1];
    FILE *fileopened = fopen(tfile, "r");
    if (fileopened == NULL)
    {
        return 2;
    }


    BYTE buffer[BLOCK];
    int count = 0;

    FILE *output = NULL;
    char name[8];


    while (true)
    {
        size_t read = fread(buffer, sizeof(BYTE), BLOCK, fileopened);

        if (read == 0 && feof(fileopened))
        {
            break;
        }


        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0 && output != NULL)
        {
            fclose(output);
            count++;
        }

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(name, "%03i.jpg", count);
            output = fopen(name, "w");


        }

        if (output != NULL)
        {
            fwrite(buffer, sizeof(BYTE), read, output);

        }
    }

    fclose(output);
    fclose(fileopened);

    return 0;


}
