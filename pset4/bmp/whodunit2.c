/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[1];
    char* outfile = argv[2];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            
            RGBTRIPLE white = { 0xff, 0xff, 0xff };
            RGBTRIPLE green = { 0x00, 0xff, 0x00 }; 
            RGBTRIPLE purple = { 0xa0, 0x20, 0xf0 };
            RGBTRIPLE yellow = { 255,255,0 };
            RGBTRIPLE khaki = { 240,230,140 };
            RGBTRIPLE dkhaki = { 240,230,140 };
            RGBTRIPLE dgrod = { 184,134,11 };
            RGBTRIPLE grod = { 218,165,32 };
            RGBTRIPLE tan = { 210,180,140 };
            RGBTRIPLE burlywood = { 222,184,135 };
            RGBTRIPLE peru = { 205,133,63 };
            RGBTRIPLE sandybrown = { 244,164,96 };
            RGBTRIPLE sienna = { 160,82,45 };
            RGBTRIPLE saddlebrown = { 139,69,19 };
            RGBTRIPLE dgreen = { 0, 100, 0 };
            RGBTRIPLE teal = { 0x00, 0x80, 0x80 };
            RGBTRIPLE dsg = { 47,79,79 };
            RGBTRIPLE sb = { 70,130,180 };
            RGBTRIPLE mb = { 25,25,112 };        
            RGBTRIPLE cyan = { 0,255,255 };
            RGBTRIPLE turk = { 64,224,208 };
            RGBTRIPLE dturk = { 0,206,209 };
            RGBTRIPLE am = { 127,255,212 };
            RGBTRIPLE plum = { 221,160,221 };
            RGBTRIPLE violet = { 238,130,238 };
            RGBTRIPLE magenta = { 255,0,255 };
            RGBTRIPLE dor = { 153,50,204 };
            RGBTRIPLE mor = { 186,85,211 };
            RGBTRIPLE lsg = { 32,178,170 };
            RGBTRIPLE sg = { 46,139,87 };
            
            


            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
           
           //COLORIAMO !
           //red to white
           if ( triple.rgbtBlue == 0x00 && triple.rgbtGreen == 0x00 && triple.rgbtRed == 0xff )
                fwrite(&white, sizeof(RGBTRIPLE), 1, outptr);
           //make background green
           else if ( triple.rgbtBlue == 0xf6 && triple.rgbtGreen == 0xf6 && triple.rgbtRed == 0xec )
                fwrite(&green, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xef && triple.rgbtGreen == 0xef && triple.rgbtRed == 0xdc )
                fwrite(&cyan, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xe9 && triple.rgbtGreen == 0xe9 && triple.rgbtRed == 0xcf )
                fwrite(&turk, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xe9 && triple.rgbtGreen == 0xe9 && triple.rgbtRed == 0xd0 )
                fwrite(&dturk, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xe8 && triple.rgbtGreen == 0xe8 && triple.rgbtRed == 0xcd )
                fwrite(&am, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xea && triple.rgbtGreen == 0xea && triple.rgbtRed == 0xd1 )
                fwrite(&plum, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xea && triple.rgbtGreen == 0xea && triple.rgbtRed == 0xd2 )
                fwrite(&violet, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xea && triple.rgbtGreen == 0xea && triple.rgbtRed == 0xd3 )
                fwrite(&magenta, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xec && triple.rgbtGreen == 0xec && triple.rgbtRed == 0xd5 )
                fwrite(&dor, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xec && triple.rgbtGreen == 0xec && triple.rgbtRed == 0xdb )
                fwrite(&mor, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xed && triple.rgbtGreen == 0xed && triple.rgbtRed == 0xd9 )
                fwrite(&lsg, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xeb && triple.rgbtGreen == 0xeb && triple.rgbtRed == 0xd4 )
                fwrite(&sg, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xf1 && triple.rgbtGreen == 0xf1 && triple.rgbtRed == 0xe0 )
                fwrite(&khaki, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xf1 && triple.rgbtGreen == 0xf1 && triple.rgbtRed == 0xdf )
                fwrite(&dkhaki, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xf0 && triple.rgbtGreen == 0xf0 && triple.rgbtRed == 0xdf )
                fwrite(&yellow, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xf2 && triple.rgbtGreen == 0xf2 && triple.rgbtRed == 0xe3 )
                fwrite(&dgrod, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xf2 && triple.rgbtGreen == 0xf2 && triple.rgbtRed == 0xe4 )
                fwrite(&grod, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xf3 && triple.rgbtGreen == 0xf3 && triple.rgbtRed == 0xe5 )
                fwrite(&tan, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xf3 && triple.rgbtGreen == 0xf3 && triple.rgbtRed == 0xe6 )
                fwrite(&burlywood, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xf4 && triple.rgbtGreen == 0xf4 && triple.rgbtRed == 0xe8 )
                fwrite(&peru, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xf4 && triple.rgbtGreen == 0xf4 && triple.rgbtRed == 0xe7 )
                fwrite(&sandybrown, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xf5 && triple.rgbtGreen == 0xf5 && triple.rgbtRed == 0xea )
                fwrite(&sienna, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xf7 && triple.rgbtGreen == 0xf7 && triple.rgbtRed == 0xee )
                fwrite(&saddlebrown, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xf8 && triple.rgbtGreen == 0xf8 && triple.rgbtRed == 0xf1 )
                fwrite(&dgreen, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xf9 && triple.rgbtGreen == 0xf9 && triple.rgbtRed == 0xf2 )
                fwrite(&teal, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xf9 && triple.rgbtGreen == 0xf9 && triple.rgbtRed == 0xf3 )
                fwrite(&dsg, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xfa && triple.rgbtGreen == 0xfa && triple.rgbtRed == 0xf4 )
                fwrite(&sb, sizeof(RGBTRIPLE), 1, outptr);
           else if ( triple.rgbtBlue == 0xfc && triple.rgbtGreen == 0xfc && triple.rgbtRed == 0xf9 )
                fwrite(&mb, sizeof(RGBTRIPLE), 1, outptr);
           else
                // write RGB triple to outfile
                fwrite(&purple, sizeof(RGBTRIPLE), 1, outptr);
                
        
        
        
        
        
        
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
