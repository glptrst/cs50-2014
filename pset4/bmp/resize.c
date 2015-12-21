#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main (int argc, char * argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy n infile outfile\n");
        return 1;
    }
    
    //store argv[1] as integer using atoi function
    int n = atoi(argv[1]);
    if ( n < 1 || n > 100)
    {
        printf(" 1 < n > 100 !\n");
        return 100;
    }
    
    char* infile = argv[2];
    char* outfile = argv[3];
    
    //open infile using a pointer stored in inptr
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }
    
    // open outfile using a pointer stored in outptr
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    
    // read infile's BITMAPFILEHEADER in &infilebf
    BITMAPFILEHEADER infilebf, tempbf;
    fread(&infilebf, sizeof(BITMAPFILEHEADER), 1, inptr);
    fseek(inptr, 0, SEEK_SET);
    fread(&tempbf, sizeof(BITMAPFILEHEADER), 1, inptr);
    //gdb ci conferma che i membri di infilebf e tempbf hanno gli stessi valori
    
    
    // read infile's BITMAPINFOHEADER in &infilebi
    BITMAPINFOHEADER infilebi, tempbi;
    fread(&infilebi, sizeof(BITMAPINFOHEADER), 1, inptr);
    fseek(inptr, -(sizeof(BITMAPINFOHEADER)), SEEK_CUR );
    fread(&tempbi, sizeof(BITMAPINFOHEADER), 1, inptr);
    //gdb ci conferma che i membri di infilebi e tempbi hanno gli stessi valori
    
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (infilebf.bfType != 0x4d42 || infilebf.bfOffBits != 54 || infilebi.biSize != 40 || 
        infilebi.biBitCount != 24 || infilebi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // determine padding 
    int infilePadding =  (4 - (infilebi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int outfilePadding =  ( (4 - (    infilebi.biWidth * n   )     * sizeof(RGBTRIPLE)) % 4) % 4;
    
    
    // usata prima :tempbi.biSizeImage = (infilebi.biSizeImage * ( n * n) ) * 3 + outfilePadding ;
    tempbi.biWidth = infilebi.biWidth * n;
    tempbi.biHeight = infilebi.biHeight * n;
    // usata seconda: tempbi.biSizeImage = (  ( (tempbi.biWidth) * (tempbi.biHeight) ) * 3 ) + (outfilePadding*tempbi.biHeight);
    tempbi.biSizeImage = (tempbi.biWidth * sizeof(RGBTRIPLE) + outfilePadding) * abs(tempbi.biHeight); 
    tempbf.bfSize = tempbi.biSizeImage + 54;
    /* gdb ci conferma che i valori sono cambiati correttamente all'interno 
       di tempbf e tempbi 
    */
    
    

    
    if ( n != 1) {
    
        // write outfile's BITMAPFILEHEADER from tempbf
        fwrite(&tempbf, sizeof(BITMAPFILEHEADER), 1, outptr);

        // write outfile's BITMAPINFOHEADER from tempbi
        fwrite(&tempbi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(infilebi.biHeight); i < biHeight; i++)
        {
    
            // iterate over pixels in infile's scanline
            for (int j = 0; j < infilebi.biWidth; j++)         
            {
                // temporary storage
                RGBTRIPLE triple;   
               
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile (ogni triple, cioe' ogni pixel
                //                              dev'essere riscritto n volte)
                for ( int k = 0; k < n; ++k)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }  
            // add padding to outfile
            for (int k = 0; k < outfilePadding; k++)
            {
                fputc(0x00, outptr);
            }
            
            
            for (int t = 0; t < n-1; t++)
            {
                //ritorno indietro in infile 
                fseek(inptr, -(infilebi.biWidth)*3 ,SEEK_CUR);
                
                //e copio-incollo ancora
                
                // iterate over pixels in infile's scanline
                for (int j = 0; j < infilebi.biWidth; j++)         
                {
                    // temporary storage
                    RGBTRIPLE triple;   
                   
                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                    // write RGB triple to outfile (ogni triple, cioe' ogni pixel
                    //                              dev'essere riscritto n volte)
                    for ( int k = 0; k < n; ++k)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }  
                // add padding to outfile
                for (int k = 0; k < outfilePadding; k++)
                {
                    fputc(0x00, outptr);
                }
            
            }
            
            

           
            // skip over padding, if any
            fseek(inptr, infilePadding, SEEK_CUR);
    
    }
    
    
    }
    //se n = 1 l'immagine viene soltato copiata.
    else {
        // write outfile's BITMAPFILEHEADER from tempbf
        fwrite(&infilebf, sizeof(BITMAPFILEHEADER), 1, outptr);

        // write outfile's BITMAPINFOHEADER from tempbi
        fwrite(&infilebi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(infilebi.biHeight); i < biHeight; i++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < infilebi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }

            // skip over padding, if any
            fseek(inptr, infilePadding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < outfilePadding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    
    }
     
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);
      
    //Is that all folks?
    return 0;
}
