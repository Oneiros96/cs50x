#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h> //strlng
#include <math.h> //round function

void count(string sentence);
float letters = 0;
float words = 0;
float sentences = 0;

int main(void)
{
    string sentence = get_string("Text: ");
    count(sentence);
    words = words + 1; //there is 1 more word in the input than
    float grade = 0.0588 * (letters / words * 100) - 0.296 * (sentences / words * 100) - 15.8; //Coleman-Liau index.
    int roundgrade = round(grade);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", roundgrade);
    }
}

void count(string sentence)
{
    for (int i = 0, n = strlen(sentence); i < n; i++) // loops throug evry char of the string
    {
        if (isupper(sentence[i]) || islower(sentence[i])) //if it is a letter
        {
            letters++;
        }
        else if (sentence[i] == ' ') //if it is space marking a new word
        {
            words++;
        }
        else if (sentence[i] == '!' || sentence[i] == '.' || sentence[i] == '?') // if it is ! ? . markin a new sentence
        {
            sentences++;
        }
    }
}