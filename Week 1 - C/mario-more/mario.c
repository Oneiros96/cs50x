#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int zeile = 1;
    int counter = 0;
    int anzahlzeilen;
    do
    {
        anzahlzeilen = get_int("Height:");
    }

    while (anzahlzeilen < 1 || anzahlzeilen > 8);

    for (zeile = 1; zeile <= anzahlzeilen; zeile++)
    {
        for (counter = 0; counter < anzahlzeilen - zeile; counter++) //print (anzahl zeilen - aktuelle zeile) * leerzeichen
        {
            printf(" ");
        }

        for (counter = 0; counter < zeile; counter++) //print (aktuelle zeile) * # linke seite der pyramide
        {
            printf("#");
        }

        printf("  ");

        for (counter = 0; counter < zeile; counter++) //print (aktuelle zeile) * # rechte seite der pyramide
        {
            printf("#");
        }

        printf("\n");
    }
}