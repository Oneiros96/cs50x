#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // check for and print winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    int score = 0;
    //arrays for lower and upper letters with position in array == position in alphabet
    char LOWER[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char UPPER[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    //loop length of word times
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        //check if letter on position i (loopcycle) is an upper letter
        if (isupper(word[i]))
        {
            int x = 0;
            //checks positition of current letter in alphabet
            while (word[i] != UPPER[x])
            {
                x++;
            }
            //adds value of this letter to score
            score = score + POINTS[x];

        }
        //same as above for lower letters
        else if (islower(word[i]))
        {
            int x = 0;
            while (word[i] != LOWER[x])
            {
                x++;
            }
            score = score + POINTS[x];
        }
    }
    //return final score to main
    return score;
}
