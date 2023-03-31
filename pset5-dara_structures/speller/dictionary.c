// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
//original 26, squared it to have buckets for aa ab etc.
const unsigned int N = 676;

// Hash table
node *table[N];
unsigned int words_in_dict = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hashed = hash(word);
    //sets temp to content of table at position <hashvalue of word>
    node *temp = table[hashed];
    while (temp != NULL)
    {
        if (strcasecmp(temp->word, word) == 0)
        {
            return true;
        }
        else
        {
            temp = temp->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //for cs50 Staff: got the idea to multiply first char by 26 from "https://stackoverflow.com/questions/64087044/do-you-have-any-simple-hash-function-that-takes-first-three-letter"
    //rest of the function existed befor reading this but with other (and obviously false) multiplyer
    //i'm using 26 instead of 27 because he also checks for apostrophes which in my opinion isn't nessesary when only checking for the first two letters instead of his three
    int hashed = 0;
    //if word has only 1 char like a in i need a coffee
    //hash funktion should generate an int between 0 and 675, depending on the first 2 chars of the word
    //the word a would be 0 a hyphothetical word starting with zz would be 675
    if (strlen(word) == 1)
    {
        hashed = ((tolower(word[0]) - 97) *  26) + (tolower(word[0]) - 97);
    }
    else
    {
        hashed = ((tolower(word[0]) - 97) * 26) + (tolower(word[1]) - 97);
    }
    return hashed;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //open fle and return false if sth. went wrong
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }
    //lenght+1 because strings end with \0
    char temp[LENGTH];
    while (fscanf(dict, "%s", temp) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        //if memory cant be allocated (not enough memory etc.)
        if (new_node == NULL)
        {
            return false;
        }
        //copye word into ne node and make it point to NULL
        strcpy(new_node->word, temp);
        new_node->next = NULL;
        int hash_value = hash(temp);
        //if hashtable at index hash_value is empty replace it with new node
        if (table[hash_value] == NULL)
        {
            table[hash_value] = new_node;
        }
        //else make new_node->next point to current node at table[hash_value] and make new_node the new first item in table[hash_value]
        else
        {
            new_node->next = table[hash_value];
            table[hash_value] = new_node;
        }
        words_in_dict++;
    }
    fclose(dict);
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    return words_in_dict;

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *current = table[i];
        node *temp = table[i];
        while (current != NULL)
        {
            current = current->next;
            free(temp);
            temp = current;
        }
    }
    return true;
}
