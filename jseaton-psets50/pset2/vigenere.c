#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Ensure Key Exists
    if (argc != 2)
    {
        printf("Not cool...\n");
        return 1;
    }
    // Ensure Key is Alphabetical
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            // Terminate
            printf("Not cool...\n");
            return 1;
        }
    }
    // Get message
    string message = GetString();
    char code;
    
    // Delcare Array Size of Message
    char key[strlen(message)];
    
    // Fill array with key
    for (int i = 0, j = 0, n = strlen(message); i < n; i++)
    {
        if isalpha(message[i])
        { 
            key[i] = ((argv[1])[j % strlen(argv[1])]);
            j++;
        }
        else
        {
            key[i] = (message[i]);
        }
    }
    
    //Encode
    for (int i = 0, n = strlen(message); i < n; i++)
    {
        // Letters
        if (isalpha(message[i]))
            {
                // Base Letter
                char base;
                if (isupper(message[i]))
                {
                    base = 'A';
                }
                else 
                {
                    base = 'a';
                }
                // Upper Case
                if (isupper(key[i]))
                {
                    // Encode
                    code = ((message[i] + ((key[i] - 'A')-base))%26) + base;
                    printf("%c", code);
                   
                }
                // Lower Case
                if (islower(key[i]))
                {
                    // Encode
                   code = ((message[i] + ((key[i] - 'a')-base))%26) + base;
                   printf("%c", code);
                    
                }
                
            }
            // Other Characters
            else
            {
                printf("%c", message[i]);
            }
    }
    // Space at End
    printf("\n");
}
