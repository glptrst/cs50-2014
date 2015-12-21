#include <stdio.h>
#include <cs50.h>
#include <math.h> // needed for round()

int main(void)
{
    float change;
    do
    {
        printf("How much change is owed?\n");
        change = GetFloat();
        change *= 100; // makes the value in cents
        change = roundf(change); // avoids float imprecision
    }
    while(change < 0); // our change should be greater than or equal to zero

    int n;
    for(n = 0; change > 0;n = n + 1) // Loop that let us use always the 
                                     // biggest coin till the owed change is 0
    {
        if (change >= 25)
            change -= 25;
        else if (change >= 10 && change < 25)
            change -= 10;
        else if (change >= 5 && change < 10)
            change -= 5;
        else if (change >= 1 && change < 5)
            change -= 1;
    }
    printf("%i\n", n); // n are the times we used a coin, 
                       // namely the number of coins used.
    return 0;
}
