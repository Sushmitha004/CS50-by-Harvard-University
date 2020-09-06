#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //int h is to store height of the pyramid
    //Height should be either greater than 1 and less than 8
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8);
    for (int i = 1; i <= h; i++)
    {
        //loop to display space
        for (int j = 1; j <= h - i; j++)
        {
            printf(" ");
        }
        //loop to display #
        for (int n = 1; n <= i; n++)
        {
            printf("#");
        }
        printf("\n");
    }
}