/****************************************************************************
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 ***************************************************************************/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

/*
 * NODE DEFINITION  
 */
typedef struct node
{
    char word[LENGTH];
    struct node * next;
}node;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

/*
 *function to transform a string in a lower case string
 *It takes the word to transform and puts the result in word1
 *returns pointer to transformed string 
 */ 
char * toLowerString ( const char * word, char * word1 );

/*
 * Hash function
 * returns the index of the hashtable bucket to place the word in
 */
int hash (const char * key);

#endif // DICTIONARY_H
