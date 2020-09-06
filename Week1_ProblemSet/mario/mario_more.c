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
        //loop to display # in right-aligned pyramid
        for (int n = 1; n <= i; n++)
        {
            printf("#");
        }
        //loop to display 2*# spaces
        for (int s = 1; s <= 2; s++)
        {
            printf(" ");
        }
        //loop to display # in left-aligned pyramid
        for (int m = 1; m <= i; m++)
        {
            printf("#");
        }
        printf("\n");
    }
}