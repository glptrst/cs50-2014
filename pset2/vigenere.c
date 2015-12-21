#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

bool isOnlyLett ( string );
bool isUp ( char );
bool isLo ( char );
char UpChar(char plain, int k);
char LoChar(char plain, int k);


int main (int argc, string argv[])
{
    if (argc == 2)//if argc is 2 we can go on

    {

        if ( isOnlyLett(argv[1]) )//if the argc[1] is made only by letters then we can go on
        {
            //INTERPRETATION OF GIVEN KEY

            string plainText;//plainText is the text to encrypt
            string k = argv[1];//argv[1] it is stored in string k
            char nk[70];//nk is k translated in numbers followoing the instructions (A=0,a=0,B=1,b=1,C=2,c=2,...)
            for (int i = 0, n = strlen(k); i < n; i++)//this loop generate nk from k
            {
                if ( isUp( k[i] ) )
                {
                    nk[i] = k[i] - 65;
                }
                else if ( isLo( k[i] ) )
                {
                    nk[i] = k[i] - 97;
                }
            }








            //GETTING PLAIN TEXT
            plainText = GetString();//We get the plain text to encrypt from the user

            for (int i = 0, j = 0; i < strlen(plainText); i++)//i is the lettere of plainText, j is the letter in the key
            {
                if ( isUp (plainText[i]) )// if it's an uppercase letter
                {
                    printf("%c", UpChar(plainText[i],nk[j]) );//we encrypt it and show the result

                    if ( j == strlen(k) - 1 )//j grows up
                    {                        //for every letter (not every char)
                        j = 0;              //and when j is the last letter of the key
                    }                       //we set it to 0
                    else                    //so the key is used from the beginning again
                    {
                        j++;
                    }
                }
                else if ( isLo ( plainText[i] ) )// if it's a lower case letter
                {
                    printf("%c", LoChar(plainText[i], nk[j]) );//we encrypt it and show the result

                    if ( j == strlen(k) - 1 )//the same as above
                    {
                        j = 0;
                    }
                    else
                    {
                        j++;
                    }
                }
                else// if it's not a letter we just reprint the same char
                {   // j remains the same
                    printf("%c", plainText[i]);
                }
            }
            printf("\n");
        }
        else
        {
            printf("Your key is not correct!\n");
            return 1;
        }
    }
    else if (argc == 1)   //if argc is 1 then complain and error!
    {
        printf("Give me a key!\n");
        return 1;
    }
    else
    {
        printf("Give me just one key!\n");
        return 1;       // if argc is more than 2 then error!
    }
}




//function which checks if a string is made only by letters
bool isOnlyLett ( string p )
{
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        if ( !(isUp ( p[i] )) && !(isLo ( p[i] )) )
        {
            return false;
            break;
        }
    }

    return true;
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
