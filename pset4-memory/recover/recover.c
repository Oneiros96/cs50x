#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;
const int blocksize = 512;


void recover(FILE *input, BYTE *block, FILE *output);
void is_new_file(FILE *input, BYTE *block, FILE *output);

int main(int argc, char *argv[])
{
    //checks if startet with correct ammount of parameters
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    //open input
    FILE *input = fopen(argv[1], "r");
    FILE *output = NULL;
    //buffer for blocks
    BYTE *block = malloc(512 * sizeof(BYTE));
    char file_name[8];
    int number_of_files = 0;
    bool found_img = false;
    bool is_first_img = true;

    //until end of input file
    while (fread(block, sizeof(BYTE), blocksize, input) == blocksize)
    {
        //checks for start of new image
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            found_img = true;
            //always false after 1. found image
            if (is_first_img)
            {
                is_first_img = false;
            }
            else
            {
                //closes current open output file when a new file is found and it isnt the first one
                fclose(output);
            }
            //generates formatet string xxx.jpeg xxx=number_of_files
            sprintf(file_name, "%03i.jpg", number_of_files);
            output = fopen(file_name, "w");
            //writes from buffer to output
            fwrite(block, sizeof(BYTE), blocksize, output);
            number_of_files++;
        }
        else
        {
            //if there is a found image continue writing to it
            if (found_img)
            {
                fwrite(block, sizeof(BYTE), blocksize, output);
            }
        }
    }
    fclose(input);
    fclose(output);
    free(block);
    return 0;
}

