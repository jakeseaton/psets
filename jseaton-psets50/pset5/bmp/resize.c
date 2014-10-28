/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h" 
#define BITSPERROW 32

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile \n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    int n = atoi(argv[1]);
    
    if (n < 1 || n > 100 )
    {
        printf("n must be an integer between 1 and 100");
        return 1;
    }
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
 
    // determine old padding for scanlines
    int oldpadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    
    // update height and width
    bi.biWidth *= n;
    bi.biHeight *= n;
    
    // determine new padding for scanlines
    int newpadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // change header variables
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth + newpadding) * abs(bi.biHeight));
    bf.bfSize = (bf.bfOffBits + bi.biSizeImage);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // temporary storage array 
    RGBTRIPLE newrow[bi.biWidth];
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight / n); i < biHeight; i++)
    {
        // initiailize counter
        int counter = 0;
        
        // iterate over pixels in scanline
        for (int j = 0; j < (bi.biWidth / n); j++)
        {
            // temporary storage triple
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // fill temporary array
            for (int i = 0; i < n; i++)
            {
                newrow[counter] = triple;
                counter++;
            }
        }
        // write RGB triple to outfile n times
        for (int k = 0; k < n; k++)
        {
            // write the pixels
            fwrite(newrow, sizeof(RGBTRIPLE), bi.biWidth, outptr);
            
            // add padding
            for (int l = 0; l < newpadding; l++)
            {
                fputc(0x00, outptr);
            }
            
        }
        
        // skip over padding, if any
        fseek(inptr, oldpadding, SEEK_CUR);

        
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
