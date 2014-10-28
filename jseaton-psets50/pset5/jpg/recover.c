#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

#define STDSIZE 512
#define DELETEDIMAGES 50

// initialize
int counter = 0;
char title[9];
unsigned char buffer[STDSIZE];
FILE* recoveredimage;

int main(void)
{
    FILE* card = fopen("card.raw", "r");
    while (fread(&buffer, STDSIZE, 1, card) == 1)
    {
        // if start of new jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            if (buffer[3] == 0xe0 || buffer[3] == 0xe1)
            {
                // close previous picture
                if (counter > 0)
                {
                    fclose(recoveredimage);
                } 
                
                // recover picture
                sprintf(title, "%.3d.jpeg", counter);
                recoveredimage = fopen(title, "w");
                fwrite(&buffer, STDSIZE, 1, recoveredimage);
                
                // increment counter
                counter++;
            }
        }
        // else it is part of the jpeg, so write it
        else if (counter > 0) 
        {
            fwrite(&buffer, STDSIZE, 1, recoveredimage);
        }
        
    }
    fclose(card);
}
