#include <stdio.h>
#include <cs50.h>

void initials(string); //function that gets a string with a full name and prints uppercase initials
void makeup(int);      //function that makes a char into an uppercase char



int main (void)
{
    string FullName;
    // User writes his full name. It'll be the value of FullName.
    FullName = GetString();
    // We use this function to print uppercase initials.
    initials(FullName);


    return 0;
}



// function which gives initials
void initials(string name)
{
    // printf the first initial
    makeup(name[0]);
    // printf other initials:
    //till we don't get to the null sign test every char
    //and if a char is a space we print the next char in uppercase
    int i = 1;
    while (name[i] != '\0')
    {
        i++;
        if (name[i] == ' ')
        {
            makeup(name[i + 1]);
        }
    }
    // print a new line
    printf("\n");
}


//function that makes a char into an uppercase char
void makeup(int a)
{
    if (a > 64 && a < 91)
        printf("%c", a);
    else
        printf("%c", a - 32);
}
