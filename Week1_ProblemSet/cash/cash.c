#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dollar;
    do
    {
        dollar = get_float("Change owed: ");
    }
    while (dollar < 0);
    //Since the coins are in cents, amount in dollar should be converted into cents
    int cents = round(dollar * 100);
    int coins = 0;
    while (cents != 0)
    {
        //if the cent value is more than 25, consider first if block
        if (cents >= 25)
        {
            cents = cents - 25;
        }
        //if the cent value is more than or equal to 10 and less than 25, consider first else if block
        else if (cents >= 10 && cents < 25)
        {
            cents = cents - 10;
        }
        //if the cent value is more than or equal to 5 and less than 10, consider second else if block
        else if (cents >= 5 && cents < 10)
        {
            cents = cents - 5;
        }
        //if the cent value is more than or equal to 1 and less than 5, consider third else if block
        else if (cents >= 1 && cents < 5)
        {
            cents = cents - 1;
        }
        //when cent value becomes 0, break from the while loop
        else
        {
            break;
        }
        coins = coins + 1;

    }
    printf("%i\n", coins);
}