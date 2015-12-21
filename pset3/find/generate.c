/***************************************************************************
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 ***************************************************************************/
 
// standard libraries
#define _XOPEN_SOURCE
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // if we execute the program with too few or too many arguments
    // then show the correct usage and return 1.
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // function atoi converts a string to an integer
    // In this case is used for argv[1], i.e. the number of
    // numbers the program should generate.   
    int n = atoi(argv[1]);

    // srand48 is a function used to seed drand48.
    // If the arguments are two, we use the argv[2] as a seed.
    // Otherwise: we use the time as a seed. 
    //  "The call to time(NULL) returns the current
    // calendar time" (from stack overflow). 
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    // TODO: we print pseudorandom numbers using drand48
    // and multiplicating to LIMIT..
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
