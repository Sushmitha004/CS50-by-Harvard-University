#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    int key = 0;
    string text;

    //checking if only 2 command line arguments are present including ./caesar
    if (argc == 2)
    {
        int n = strlen(argv[1]);

        //checking if all the characters in the given argument are digits or not
        for (int i = 1; i < argc; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (isalpha(argv[i][j]))
                {
                    printf("Usage: ./caesar key\n");
                    return 1;
                }
            }
        }

        //convert the argument from type string to type int
        key = atoi(argv[1]);
        printf("key: %i\n", key);

        //get a text from the user
        text = get_string("plaintext: ");
        // printf("%s\n", text);

        int len_text = strlen(text);
        int c_text[len_text];

        printf("ciphertext: ");
        int p = 0;

        //Encrypting the given text
        while (text[p] != '\0')
        {
            if(isupper(text[p]))
            {
                text[p] -= 65;
                // printf("text = %i\n", text[p]);

                c_text[p] = (text[p] + key) % 26;

                c_text[p] += 65;
                // printf("c_text = %i\n", c_text[p]);

                printf("%c", c_text[p]);

                p++;
            }
            else if (islower(text[p]))
            {
                text[p] -= 97;
                // printf("text = %i\n", text[p]);

                c_text[p] = (text[p] + key) % 26;

                c_text[p] += 97;
                // printf("c_text = %i\n", c_text[p]);

                printf("%c", c_text[p]);

                p++;
            }
            else
            {
                c_text[p] = text[p];

                printf("%c", c_text[p]);
                p++;
            }
        }

        printf("\n");
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}