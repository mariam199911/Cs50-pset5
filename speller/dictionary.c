// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include<stdint.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"
int size_word;
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 5382;

// Hash table
node *table[N];


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    char tmp[strlen(word)];
    strcpy(tmp, word);
    for (int i = 0; i < strlen(word); i++)
    {
        tmp[i] = tolower(word[i]);
    }
    node *cursor = table[hash(tmp)];
    while (cursor != NULL)
    {
        if (strcmp(cursor->word, tmp) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor -> next;
        }
    }
    
    return false;
}
    

// Hashes word to a number
//#define MULTIPLIER (37)
unsigned int hash(const char *word)
{
    // TODO
    unsigned long hash = (N - 1);
    int c = 0;
    while (c == *word++)
    {
        hash = c + ((hash << 5) + hash);
    }
    return hash % (N - 1);
   
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    for (int s = 0; s < N; s++)
    {
        table[s] = NULL;
    }
    FILE *file = fopen(dictionary, "r"); //fdbdghtrmhjtrln
    if (file == NULL)
    {
        return 1;
    }
    char tempword[LENGTH + 1];
    while (fscanf(file, "%s", tempword) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            unload();
            fclose(file);
            return false;
        }
        strcpy(n-> word, tempword);
        int i = hash(n-> word);
        if (table[i] == NULL)
        {
            table[i] = n;
            n->next = NULL;
            (size_word++);
        }
        else
        {
            n->next = table[i];
            table[i] = n;
            (size_word++);
        }  
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return size_word;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int s = 0; s < N; s++)
    {
        node *cursor = table[s];
        
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor -> next;
            free(temp);
        }    
    }
    
    return true;
}


