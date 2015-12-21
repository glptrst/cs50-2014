#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;

    do  // if we use scanf instead of GetInt there is problem...
    {
        printf("Give me a number between 0 and 23.\n");
        printf("It'll be the height of your half-pyramid: ");
        height = GetInt();            
    }
    while (height < 0 || height > 23);

    for (int n = 0; n < height; n++)
    {
        for(int spaces = 0; spaces < height - (n + 1); spaces++)
        {
            printf(" ");  // print the right number of spaces
        }    

        for(int hashes = 0; hashes < n + 2; hashes++)
        {    
            printf("#");  // print the right number of hashes
        }    

        printf("\n");     // new line
    }
    return 0;
}
