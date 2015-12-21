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
            RGBTRIPLE black = { 0x00, 0x00, 0x00 };
            RGBTRIPLE red = { 0x00, 0x00, 0xff };
            RGBTRIPLE green = { 0x00, 0xff, 0x00 }; 
            RGBTRIPLE blue = { 0xff, 0x00, 0x00 };
            RGBTRIPLE dark_goldenrod = { 0xb8, 0x86, 0x0b };
            RGBTRIPLE purple = { 0xa0, 0x20, 0xf0 };

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            if ( triple.rgbtBlue == 0x00 && triple.rgbtGreen == 0x00 && triple.rgbtRed == 0xff )
                fwrite(&white, sizeof(RGBTRIPLE), 1, outptr);
            else if ( (triple.rgbtBlue == 0xec && triple.rgbtGreen == 0xec && triple.rgbtRed == 0xd6) ||
                      (triple.rgbtBlue == 0xea && triple.rgbtGreen == 0xea && triple.rgbtRed == 0xd1) ||
                      (triple.rgbtBlue == 0xec && triple.rgbtGreen == 0xec && triple.rgbtRed == 0xd5) ||
                      (triple.rgbtBlue == 0xf3 && triple.rgbtGreen == 0xf3 && triple.rgbtRed == 0xe6) ||
                      (triple.rgbtBlue == 0xf8 && triple.rgbtGreen == 0xf8 && triple.rgbtRed == 0xf0) ||
                      (triple.rgbtBlue == 0xf9 && triple.rgbtGreen == 0xf9 && triple.rgbtRed == 0xf3) ||
                      (triple.rgbtBlue == 0xfb && triple.rgbtGreen == 0xfb && triple.rgbtRed == 0xf6) ||
                      (triple.rgbtBlue == 0xea && triple.rgbtGreen == 0xea && triple.rgbtRed == 0xd1) ||
                      (triple.rgbtBlue == 0xf4 && triple.rgbtGreen == 0xf4 && triple.rgbtRed == 0xe8) ||
                      (triple.rgbtBlue == 0xf5 && triple.rgbtGreen == 0xf5 && triple.rgbtRed == 0xea)
            
            )
                fwrite(&black, sizeof(RGBTRIPLE), 1, outptr);
            else if ( (triple.rgbtBlue == 0xea && triple.rgbtGreen == 0xea && triple.rgbtRed == 0xd2) ||
                      (triple.rgbtBlue == 0xf5 && triple.rgbtGreen == 0xf5 && triple.rgbtRed == 0xfa) ||
                      (triple.rgbtBlue == 0xe9 && triple.rgbtGreen == 0xe9 && triple.rgbtRed == 0xcf) ||
                      (triple.rgbtBlue == 0xfa && triple.rgbtGreen == 0xfa && triple.rgbtRed == 0xf4) ||
                      (triple.rgbtBlue == 0xed && triple.rgbtGreen == 0xed && triple.rgbtRed == 0xd7) ||
                      (triple.rgbtBlue == 0xf7 && triple.rgbtGreen == 0xf7 && triple.rgbtRed == 0xee) ||
                      (triple.rgbtBlue == 0xe8 && triple.rgbtGreen == 0xe8 && triple.rgbtRed == 0xcc) ||
                      (triple.rgbtBlue == 0xef && triple.rgbtGreen == 0xef && triple.rgbtRed == 0xdd)
            )
                fwrite(&red, sizeof(RGBTRIPLE), 1, outptr);
            else if (triple.rgbtBlue == 0xf6 && triple.rgbtGreen == 0xf6 && triple.rgbtRed == 0xec)
                fwrite(&green, sizeof(RGBTRIPLE), 1, outptr);
            else if ( (triple.rgbtBlue == 0xf9 && triple.rgbtGreen == 0xf9 && triple.rgbtRed == 0xf2) ||
                      (triple.rgbtBlue == 0xf8 && triple.rgbtGreen == 0xf8 && triple.rgbtRed == 0xf1) ||
                      (triple.rgbtBlue == 0xe9 && triple.rgbtGreen == 0xe9 && triple.rgbtRed == 0xd0) ||
                      (triple.rgbtBlue == 0xe8 && triple.rgbtGreen == 0xe8 && triple.rgbtRed == 0xcd) ||
                      (triple.rgbtBlue == 0xf7 && triple.rgbtGreen == 0xf7 && triple.rgbtRed == 0xed) ||
                      (triple.rgbtBlue == 0xf9 && triple.rgbtGreen == 0xf9 && triple.rgbtRed == 0xf3) ||
                      (triple.rgbtBlue == 0xeb && triple.rgbtGreen == 0xeb && triple.rgbtRed == 0xd4) ||
                      (triple.rgbtBlue == 0xf6 && triple.rgbtGreen == 0xf6 && triple.rgbtRed == 0xeb) ||
                      (triple.rgbtBlue == 0xea && triple.rgbtGreen == 0xea && triple.rgbtRed == 0xd3) ||
                      (triple.rgbtBlue == 0xf0 && triple.rgbtGreen == 0xf0 && triple.rgbtRed == 0xdf) ||
                      (triple.rgbtBlue == 0xf4 && triple.rgbtGreen == 0xf4 && triple.rgbtRed == 0xe7)
            )
                fwrite(&blue, sizeof(RGBTRIPLE), 1, outptr);
            else if ( (triple.rgbtBlue == 0xf2 && triple.rgbtGreen == 0xf2 && triple.rgbtRed == 0xe3) ||
                      (triple.rgbtBlue == 0xf2 && triple.rgbtGreen == 0xf2 && triple.rgbtRed == 0xe4) ||
                      (triple.rgbtBlue == 0xf1 && triple.rgbtGreen == 0xf1 && triple.rgbtRed == 0xe1) ||
                      (triple.rgbtBlue == 0xf5 && triple.rgbtGreen == 0xf5 && triple.rgbtRed == 0xe9)
            
            )
                fwrite(&dark_goldenrod, sizeof(RGBTRIPLE), 1, outptr);
            else if ( (triple.rgbtBlue == 0xf1 && triple.rgbtGreen == 0xf1 && triple.rgbtRed == 0xdf) ||
                      (triple.rgbtBlue == 0xb8 && triple.rgbtGreen == 0x86 && triple.rgbtRed == 0x0b) ||
                      (triple.rgbtBlue == 0xf3 && triple.rgbtGreen == 0xf3 && triple.rgbtRed == 0xe5)
            )
                fwrite(&purple, sizeof(RGBTRIPLE), 1, outptr);
            else
                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
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
