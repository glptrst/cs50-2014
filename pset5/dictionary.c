/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/


#include "dictionary.h"

//HASHTABLE DECLARATION
node * hashtable[26];

bool loaded;

int words_counter = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int wordLength = strlen(word);
    char lowerCaseWord[ wordLength ] ;
    
    toLowerString (word, lowerCaseWord);
    
    node * cursor = hashtable[ hash(word) ];

    if ( cursor == NULL )
    {
        return false;
    }
    else
    {
        if ( strcmp( lowerCaseWord, cursor->word ) == 0 )
        {
            return true;
        }
        else
        {
            while ( cursor->next != NULL )
            {
                cursor = cursor->next;
                if ( strcmp( lowerCaseWord, cursor->word ) == 0 )
                {
                    return true;
                }
            }
        }   
        return false;
    }
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{   
    //set all pointers of hashtable to NULL
    int i;
    for (i = 0; i < 26; i++) {
        hashtable[i] = NULL;
    }
    
    FILE * inptr = fopen(dictionary, "r");
    //sanity check:
    if ( inptr == NULL )
    {
        loaded = false;
        return false;
    }
    
    for (words_counter = 0; true/*fscanf(inptr, "%s", new_node->word)!= EOF*/; words_counter++)
    {
        node * new_node = malloc( sizeof(node) );
        new_node->next = NULL;
        int result = fscanf(inptr, "%s", new_node->word);
        if ( result == EOF )
            {
                free(new_node);
                break;
            }
              
        //use the hash function to get the index
        int index1 = hash(new_node->word);

        if (hashtable[index1] == NULL) 
        {            
        //store the new node in the right bucket using the hash function 
        hashtable[index1] = new_node;
        }
        else 
        { //if it's not the first word
            new_node->next = hashtable[index1];
            hashtable[index1] = new_node;
        }        
    }
     
    fclose(inptr);
    
    loaded = true;
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return words_counter;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    if (loaded == false)
    {
        printf("Is loaded false!?\n");
        return false;
    }
    else
    {
        for ( int i = 0; i < 26; i++ )
        {
            node * cursor = hashtable[i];
            //if there are no nodes in the bucket
            if ( cursor == NULL )
                continue;
            //if there is just one node in the bucket 
            else if ( cursor->next == NULL )
            {
                free( cursor );
            }
            //if there are more nodes in the bucket
            else
            {
                node * temp = cursor;
                cursor = cursor->next;
                free(temp);
                while (cursor->next != NULL)
                {
                    node * temp = cursor; 
                    cursor = cursor->next;
                    free(temp);
                }
                free(cursor);
            }
        }
        return true;
    }
    
}

/*
 *function to transform a string in a lower case string
 *It takes the word to transform and puts the result in word1
 *returns pointer to transformed string 
 */ 
char * toLowerString ( const char * word, char * word1 )
{
    int i;
    for (i = 0; word[i]!='\0'; i++)
    {
        word1[i] = tolower(word[i]);
    }
    word1[i] = '\0';
    
    return word1;
}

/*
 * Hash function
 * returns the index of the hashtable bucket to place the word in
 */
int hash (const char * key)
{
    //hash on first letter of string
    int hash = toupper(key[0]) - 'A';
    return hash % 26;
}
