#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Get Name
    string name;
    name = GetString();
   
    // Printing Intials
    for (int i = 0; i < strlen(name); i++)
    {
        // Print After a Space
        if (name[i] == ' ')
        {
            printf("%c", toupper(name[i + 1]));
        }
        // First Initial
        if (i == 0)
        {
            // Space at Start
            if (name[i] == ' ')
            {
                i++;
            }
            else
                // Print Initial
            {
                printf("%c", toupper(name[i]));
            }
        }
    }
    // End Space
    printf("\n");
       
}
