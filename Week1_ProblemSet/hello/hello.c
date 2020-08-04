#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //variable name of type string is created to store the input from the user
    string name = get_string("What's your name?\n");
    //%s is a placeholder for variable of type string
    printf("hello, %s\n", name);
}