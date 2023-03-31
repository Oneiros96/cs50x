#include <cs50.h>
#include <stdio.h>
// #include <stdbool.h> enables bool instead of _bool and false and true as alias for 0 1 already included in cs50.h

int check();
int visa();
int amex();
int master();

int main(void)
{
    long number;
    int checksume;

    number = get_long_long("Number:");
    checksume = check(number);
    if (checksume % 10 == 0)
    {
        if (visa(number) == 1)
        {
            printf("VISA\n");
        }
        else if (amex(number) == 1)
        {
            printf("AMEX\n");
        }
        else if (master(number) == 1)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}

int check(long long i)
{
    int rest;
    int sum1 = 0;
    int sum2 = 0;
    int result;
    do
    {
        rest = i % 10;              //letzte stelle auslesen
        sum1 = sum1 + rest;         //zu summe der nicht miltiplizierten zahlen rechnen
        i = i / 10;                 //letzte stelle löschen mit /10 teilen
        rest = i % 10;              //vorletzte stelle  auslesen
        rest = rest * 2;            //mit 2 multiplizieren
        sum2 = sum2 + (rest / 10);  //fals 2 stellige zahl ergebnis vorletzte stelle
        sum2 = sum2 + (rest % 10);  //letzte stelle
        i = i / 10;

    }
    while (i > 0);
    result = sum1 + sum2;
    return result;
}

int visa(long long i)
{

    if (i > 4000000000000 && i < 5000000000000) //13 stellen beginnt mit 4
    {
        return 1;
    }
    else if (i > 4000000000000000 && i < 5000000000000000) //16stellen beginnt mit 4
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int amex(long long i)
{

    if (i > 339999999999999 && i < 350000000000000) //15 stellen lang beginnt mit 34
    {
        return 1;
    }
    else if (i > 369999999999999 && i < 380000000000000) //15 stellen beginnt mit 37
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int master(long long i)
{

    if (i > 5099999999999999 && i < 5600000000000000) //16 stellen beginnt mit 51-56
    {
        return 1;
    }
    else
    {
        return 0;
    }
}