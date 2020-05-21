/*------------------------------\
|  Code (C) 2020 Micah Lindley  |
|   Part of the CS50x course    |
|-------------------------------|
|Do not use this code to cheat! |
\------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// define a byte
typedef uint8_t BYTE;
// define the size of a block to read
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // ensure that only one command-line arguement is inputted
    if (argc > 1 && argc < 3)
    {
        // get RAW file to be processed from the user's second arguement (hint: char * is the same as string)
        char *filename = argv[1];
        // set number of JPEG files found in the RAW file
        int jpegsProcessed = 0;
        // open the RAW file
        FILE *ptr = fopen(filename, "r");
        // check if file exists
        if (ptr == NULL)
        {
            // tell the user the issue
            printf("Either that file doesn't exist or you don't have enough memory to open it.  Please try again.\n");
            // exit with an error
            return 1;
        }
        // define a buffer to read from
        unsigned char *buffer = malloc(512);
        // declare the write file
        FILE *toWrite = NULL;
        // define the filename to write to
        // it's eight characters- count: 000.jpg
        char filenameToWrite[8];
        while (true)
        {
            // read a portion of the file
            size_t bytesRead = fread(buffer, 512, 1, ptr);
            // check for the end of the file
            if (bytesRead == 0 && feof(ptr))
            {
                // break out of the loop
                break;
            }
            // check if the chunk being read matches a JPEG header using bitwise operators
            bool hasHeader = (buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0);
            // if the chunk being read has a header
            if (hasHeader)
            {
                // if a file is opened
                if (jpegsProcessed > 0)
                {
                    // close it
                    fclose(toWrite);
                }
                // print the correct filename to a string
                sprintf(filenameToWrite, "%03i.jpg", jpegsProcessed);
                // define the file to write to
                toWrite = fopen(filenameToWrite, "w");
                // increment the JPEGs processed
                jpegsProcessed++;
                // write data
                fwrite(buffer, 512, 1, toWrite);
            }
            else
            {
                if (jpegsProcessed > 0)
                {
                    // write data
                    fwrite(buffer, 512, 1, toWrite);
                }
            }
        }
        // close the file we're reading from
        fclose(ptr);
        // close any written files
        fclose(toWrite);
        // clear any allocated memory
        free(buffer);
        // exit with an okay status
        return 0;
    }
    else
    {
        // notify the user that only one arg is required
        printf("Usage: ./recover [filename]\n");
        // exit with an error
        return 1;
    }
}
