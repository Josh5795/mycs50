#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    //declare padding variable
    int padding;
    int padding2;

    // declare n an integer
    int n = atoi(argv[1]);

    // ensure proper usage
    if (argc != 4||0 > n||n > 100)
    {
        fprintf(stderr, "Usage: n ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
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

   // determine padding for infile scanlines
    padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //update info about headers
    bi.biWidth = bi.biWidth*n;
    bi.biHeight = -(abs(bi.biHeight))*n;

    // determine padding for outfile lines
    padding2 = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //continue updating info about headers
    bi.biSizeImage = ((sizeof(RGBTRIPLE)*bi.biWidth)+padding2)*abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = (abs(bi.biHeight))/n; i < biHeight; i++)
    {
        //vertically resizing: adding n rows that have been resized horizontally
        for(int l = 0; l < n-1; l++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth/n; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile n times
                for (int m = 0; m < n; m++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // add new padding value
            for (int k = 0; k < padding2; k++)
            {
                fputc(0x00, outptr);
            }

            //skip back to start of infile scan line (3 bytes to a pixel durrr)
            fseek(inptr, -((bi.biWidth*3/n)+padding), SEEK_CUR);
        }
        // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth/n; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile n times
                for (int m = 0; m < n; m++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // add new padding value
            for (int k = 0; k < padding2; k++)
            {
                fputc(0x00, outptr);
            }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
