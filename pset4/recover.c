#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./copy forensicimage\n");
        return 1;
    }

    //remember filename
    char *infile = argv[1];

    // open memory card file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open card.raw");
        return 2;
    }

    //declare block array
    uint8_t block[512];

    //declare count variable
    int count = 0;

    // temp file output
    FILE* img = NULL;

    //check if a block of 512 bytes is possible to read and read
    while(fread(block, 512, 1, inptr)==1)
    {

        //if first 4 bytes of block indicates a JPEG
        if(block[0]==0xff&&
           block[1]==0xd8&&
           block[2]==0xff&&
           (block[3] & 0xf0) == 0xe0)
        {
           //if we've already found a jpeg close current jpeg
           if(img != NULL)
           {
                fclose(img);
           }

           //create jpeg file name
           char filename[8];
           sprintf(filename, "%03i.jpg", count);

           //open new jpeg
           img = fopen(filename, "w");
           if(img == NULL)
           {
               fprintf(stderr, "Error opening JPEG");
               return 3;
           }

           //increase counter variable for file names
           count++;

           //write block to jpeg file
           fwrite(block, 512, 1, img);
        }

        //if the first 4 bytes of block read doesn't indicate the start of a jpeg
        else
        {

            //if we have already found a jpeg (img value isn't null anymore)
            if(img != NULL)
            {
                //write block to jpeg file
                fwrite(block, 512, 1, img);
            }

        }

    }

    //close memory card file
    fclose(inptr);

    //close jpeg file
    fclose(img);

}
