#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover filename\n");
        return 1;
    }

    // Open memory card
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("File not working\n");
        return 1;
    }

    bool flag = false;

    int counter = 0;

    FILE *img = NULL;

    char filename[50];

    // Read 512 bytes into a buffer
    unsigned char buffer[512];

    // Repeat until end of card
    while (fread(buffer, 512, 1, file) == 1)
    {
        // If start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If first JPEG
            if (flag == true)
            {
                fclose(img);
            }
            else
            {
                flag = true;
            }

            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            counter++;
        }

        if (flag == true)
        {
            fwrite(&buffer, 512, 1, img);
        }
    }

    // Close any remaining files
    fclose(file);
    fclose(img);
}

/*
1. .Open memory card
2. .Repeat until end of card
        .Read 512 bytes into a buffer
        .If start of new JPEG
            If first JPEG
                write 000.jpeg
            Else
                close the file that is already open and open new file
        Else
            If already found JPEG
                keep writing
    .Close any remaining files
*/