// recover.c
// Recovers JPEGs from a forensic image (card.raw)

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open input file
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }

    const int BLOCK_SIZE = 512;
    uint8_t buffer[BLOCK_SIZE];
    FILE *outptr = NULL;
    int file_count = 0;
    char filename[8]; // "###.jpg" + null

    // Read blocks until EOF
    size_t bytes_read;
    while ((bytes_read = fread(buffer, sizeof(uint8_t), BLOCK_SIZE, inptr)) > 0)
    {
        // Check for JPEG signature at start of block
        if (bytes_read >= 4 && buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If already writing a file, close it
            if (outptr != NULL)
            {
                fclose(outptr);
                outptr = NULL;
            }

            // Open new JPEG file
            sprintf(filename, "%03d.jpg", file_count);
            outptr = fopen(filename, "w");
            if (outptr == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", filename);
                fclose(inptr);
                return 1;
            }
            file_count++;

            // Write this block to the new file
            fwrite(buffer, sizeof(uint8_t), bytes_read, outptr);
        }
        else
        {
            // If currently writing a JPEG, keep writing blocks to it
            if (outptr != NULL)
            {
                fwrite(buffer, sizeof(uint8_t), bytes_read, outptr);
            }
            // else: haven't found a JPEG yet — skip
        }
    }

    // Clean up
    if (outptr != NULL)
        fclose(outptr);

    fclose(inptr);
    return 0;
}
