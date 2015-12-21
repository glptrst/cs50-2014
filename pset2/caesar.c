#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isUp ( char ); //checks if a char is upper case letter
bool isLo ( char ); //checks if a char is lower case letter
char UpChar ( char, int ); //FUNCTION FOR ENCRYPT A UPPERCASE LETTER.IT ACCEPTS THE CHAR AND THE "CAESAR KEY"
char LoChar ( char, int ); //FUNCTION FOR ENCRYPT A LOWERCASE LETTER.IT ACCEPTS THE CHAR AND THE "CAESAR KEY"

int main(int argc, string argv[])
{
    if (argc == 2)//our program should have just one argument (argv[1]), so argc should be 2.
    {
        int k = atoi(argv[1]); // argv[1] is originaly a string but with the atoi function we store it as an int
        string plainText = GetString(); //we prompt the user for text to encrypt, the plainText

        for (int i = 0, n = strlen(plainText); i < n; i++) //loop to iterate over every char of the plaintext
        {
            if ( isUp(plainText[i]) )     //If the char is an Uppercase letter then:
            {                                               //we encrypt it using UpChar() and we print the result
                printf("%c", UpChar(plainText[i], k));
            }
            else if ( isLo(plainText[i]) ) //If the char is a Lowecase letter then:
            {                                                 //We encrypt it using LoChar() and we print the result
                printf("%c", LoChar(plainText[i], k));
            }
            else                   //If the char is neither an Uppercase letter nor a Lowercase letter then:
            {                      //We just print the char as it is
                printf("%c", plainText[i]);
            }
        }

    //new line
    printf("\n");

    return 0;
    }
    else if (argc == 1)
    {
        printf("Give me a key!\n");
        return 1;
    }
    else
    {
        return 1;
    }

}



//FOR CHECK IF A CHAR IS A UPPERCASE LETTER
bool isUp ( char a )
{
    if( a > 64 && a < 91)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//FOR CHECK IF A CHAR IS A LOWERCASE LETTER
bool isLo ( char a )
{
    if ( a > 96 && a < 123 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

//FUNCTION FOR ENCRYPT UPPERCASE LETTERS. IT ACCEPTS THE CHAR AND THE "CAESAR KEY"
char UpChar(char plain, int k)
{
    int charEncrypted = plain + k;
    if (charEncrypted < 91) // if it doesn't go beyond z namely 90
    {
        return charEncrypted;
    }
    else // if (charEncrypted > 90) namely if it goes beyond 'Z'
    {
        do
        {
            charEncrypted = 64 + (charEncrypted % 90);
        }
        while (charEncrypted > 90);

        return charEncrypted;
    }
}

//FUNCTION FOR ENCRYPT LOWER LETTERS. IT ACCEPTS THE CHAR AND THE "CAESAR KEY"
char LoChar(char plain, int k)
{
    int charEncrypted = plain + k;
    if (charEncrypted < 123) //if it doesn't go beyond 'z' namely 122
    {
        return charEncrypted;
    }
    else // if (charEncrypted > 122) namely if it goes beyond 'z'
    {
        do
        {
            charEncrypted = 96 + (charEncrypted % 122);
        }
        while (charEncrypted > 122);

        return charEncrypted;
    }
}

