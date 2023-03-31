// Modifies the volume of an audio file

#include <stdint.h>//uint8_t & int16_t
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
void header(FILE *input, FILE *output);
void volume(FILE *input, FILE *output, float factor);
void tune(int16_t *temp, float factor, int file_size);

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    //Copy header from input file to output file
    header(input, output);
    //Read samples from input file and write updated data to output file
    volume(input, output, factor);
    // close files
    fclose(input);
    fclose(output);
}
void header(FILE *input, FILE *output)
{
    //reserviert 44 speichereinheiten größe uint8_t mit dem pointer temp
    uint8_t *temp = malloc(HEADER_SIZE);
    // ließt daten aus dem header des wave file in temp
    fread(temp, sizeof(uint8_t), HEADER_SIZE, input);
    // schreibt daten aus temp in output
    fwrite(temp, sizeof(uint8_t), HEADER_SIZE, output);
    //gibt resiervierten ram mit pointer temp wieder frei
    free(temp);
    return;

}
void volume(FILE *input, FILE *output, float factor)
{
    //setzt filepointer ans ende des inputfiles
    fseek(input, 0, SEEK_END);
    //file_size = anzahl an 2byte blöcken nach header
    int file_size = (ftell(input) - 44) / 2;
    //bewegt die stelle im File auf die der pointer zeigt (pointer, anzahl an bytes die der pointer bewegt wird, von wo beginnend)
    fseek(input, HEADER_SIZE, SEEK_SET);
    fseek(output, HEADER_SIZE, SEEK_SET);
    // reserviert file_size anzahl an 2byte blöcken ram mit pointer temp
    int16_t *temp = malloc(file_size * sizeof(int16_t));
    //ließt daten aus file in temp
    fread(temp, sizeof(int16_t), file_size, input);
    //multipliziert jeden 2byte block in temp um factor
    tune(temp, factor, file_size);
    //schreibt daten aus temp in output
    fwrite(temp, sizeof(int16_t), file_size, output);
    //gibt speicher temp wieder frei
    free(temp);
    return;
}
void tune(int16_t *temp, float factor, int file_size)
{
    for (int i = 0, n = file_size; i < n; i++)
    {
        temp[i] = temp[i] * factor;
    }
}