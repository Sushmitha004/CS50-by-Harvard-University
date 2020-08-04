#include <stdio.h>
#include <cs50.h>
#include <math.h>

bool checksum(int num[], int len);

int main(void)
{

    //loop to get positive numbers between 13 digits and 16 digits
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while (number < 0);

    //loop to find out the length of the number and to store it in an array
    int num[16], x = 0, len = 0;
    while(number != 0)
    {
        len = len + 1;
        num[x] = number % 10;
        number = number / 10;
        x++;
    }

    // printf("len = %d\n", len);

    // for(int y = 0; y < len; y++)
    // {
    //     printf("%d", num[y]);
    // }
    // printf("\n");

    bool result = false;
    if (len > 12 && len < 17)
    {
        //checksum to find out the last digit of final checksum is zero or not
        result = checksum(num, len);

        //to check different types of credit cards
        if (result == true)
        {
            if((len == 13 || len == 14 || len == 15 || len == 16) && num[len-1] == 4)
            {
                printf("VISA\n");
            }
            else if (len == 15 && (num[len-1] == 3 && (num[len-2] == 4 || num[len-2] == 7)))
            {
                printf("AMEX\n");
            }
            else if (len == 16 && (num[len-1] == 5 && (num[len-2] == 1 || num[len-2] == 2 || num[len-2] == 3 || num[len-2] == 4 || num[len-2] == 5)))
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }



}

//checksum to find out the last digit of final checksum is zero or not
bool checksum(int num[], int len)
{


    int temp[16];
    for (int b = 0; b < len; b++)
    {
        temp[b] = num[b];
    }

    int sum = 0;

    //this for loop goes through every other number, starting with the number's second-to-last digit
    for(int i = 1; i < len; i = i+2)
    {
        temp[i] = temp[i] * 2;
        //all the considered number is multiplied by 2 and all the digits are added up and stored in variable sum
        while (temp[i] != 0)
        {
            sum = sum + (temp[i] % 10);
            temp[i] = temp[i] / 10;
        }
    }
    //add up all those digits that weren't multiplied by 2
    for(int j = 0; j < len; j = j+2)
    {
        sum = sum + num[j];
    }

    // printf("sum = %d\n", sum);

    //if the last digit of final sum is zero, then the checksum is right
    if(sum % 10 == 0)
    {
    //   printf("true\n");
      return true;
    }
    else
    {
        return false;
    }
}