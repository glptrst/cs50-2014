/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t  BYTE;

int main(int argc, char* argv[])
{
    //open memory card
    FILE * inptr;
    inptr = fopen ("card.raw", "r");
    //sanity check
    if (inptr == NULL)
    {
        printf("Could not open inptr.\n");
        return 1;
    }
    
    //create pointer variable for jpg files
    FILE * outptr = NULL;
    
    //make buffer
    uint8_t buffer[512];
    //make counter
    int njpg = -1;
    //make char array for title
    char title[8];
    
    //put the read cursor in the card file right before the first jpg
    while (true)
    {
        fread(buffer, 1, 512, inptr);
    
        if ( buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && 
                             (buffer[3] == 0xe0 || buffer[3] == 0xe1)  )
            {
                fseek(inptr, -512, SEEK_CUR);
                break;
            }
    }


    while (true) // write jpgs till eof
    {
        //read 512 bytes and check for eof and jpg beginning (for the first iteration we know it'll be a jpg beginning)
        fread(buffer, 1, 512, inptr);
              
        //if eof end loop
        if ( feof(inptr) == true )
            break;
        //if jpg beginnig:
        if ( buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && 
                             (buffer[3] == 0xe0 || buffer[3] == 0xe1) )
        {   //close current jpg if any
            if ( outptr != NULL )
                fclose(outptr);
            //open new jpg
            ++njpg;
            sprintf(title, "%.3i.jpg", njpg);
            outptr = fopen(title, "a");
            //sanity check
            if (outptr == NULL)
            {
                printf("Cannot create outpt!\n");
                return 2;
            }
            
            //write the jpg
            //if we found eof put cursor one block back and end loop; the outer loop will check again and will end it too.So we finished.
            //if we found another jpg put cursor back and and loop the outer loop starts again
            while (true)
            {
                fwrite(buffer, 1, 512, outptr);
                fread(buffer, 1, 512, inptr);
                if ( feof(inptr) == true )
                {
                    fseek(inptr, -512, SEEK_CUR);
                    break;
                }
                
                if ( buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && 
                             (buffer[3] == 0xe0 || buffer[3] == 0xe1) )
                {
                    fseek(inptr, -512, SEEK_CUR);
                    break;
                }
            }
        }

    }
    
    fclose(inptr);
    if (outptr != NULL)
        fclose(outptr);
        
    return 0;
}
