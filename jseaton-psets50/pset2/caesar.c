#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Ensure Key
    if (argc != 2)
    {
        printf("Not cool...\n");
        return 1;
    }
    // Get Key
    int k = (atoi(argv[1])) % 26;
    
    // Ensure Key Positive
    if (k <= 0)
    {
        printf("Not cool...\n");
        return 1;
    }
    // Encode
    if (argc == 2)
    {
        // Get Message
        string message = GetString();
        char code;
        for (int i = 0, n = strlen(message); i < n; i++)
        {
            // Encode Letters
            if (isalpha(message[i]))
            {
                // Upper Case
                if (isupper(message[i]))
                {
                    // Encode
                    code = ((message[i] + k));
                    if (isupper(code))
                    {
                        printf("%c", code); 
                    }
                        // Wrap Around
                    else
                    {
                        code = ((message[i] + k) - 26);
                        printf("%c", code);
                    } 
                }
                // Lower Case
                if (islower(message[i]))
                {
                    // Encode
                    code = ((message[i] + k));
                    if (islower(code) && isalpha(code))
                    {
                        printf("%c", (code));
                    }
                        // Wrap Around
                   else
                    {
                        code = ((message[i] + k) - 26);
                        printf("%c", code);
                    }
                }
                
            }
                // Print Other Characters
            else
            {
                printf("%c", message[i]);
            }
        }
        printf("\n");
    }     
}
