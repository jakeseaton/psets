#include <stdio.h>
#include <cs50.h>


int main(void)
{
    // Get Height
    int height;

    do
    {
        printf("Enter Height.\n");
        height = GetInt();
    }
    while (height < 0 || height > 23 );
   
    // Print Pyramid
    for (int row = 0; row < height; row++)
    {
        for (int spaces = 0; spaces < height - row - 1; spaces++)
        {
            printf(" ");
        }
        
        for (int hash = 0; hash < row + 2; hash++)
        {
            printf("#");
        }
        printf("\n");
    }
}
