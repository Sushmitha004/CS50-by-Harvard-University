#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
void grade(int index);

int main(void)
{
    string text = get_string("Text: ");

    //function to get the number of letters in the given text
    int letters = count_letters(text);

    //function to get the number of words in the given text
    int words = count_words(text);

    //function to get the number of sentences in the given text
    int sentences = count_sentences(text);

    float L = (100 * (float)letters) / words;

    float S = (100 * (float)sentences) / words;

    //formula to calculate the Coleman-Liau index
    float index = 0.0588 * L - 0.296 * S - 15.8;

    //function to print out the grades
    grade(round(index));
}

//function to get the number of letters in the given text
int count_letters(string text)
{
    int letters = 0, i = 0;

    while (text[i] != '\0')
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
        i++;
    }
    return letters;
}

//function to get the number of words in the given text
int count_words(string text)
{
    int words = 0, i = 0;

    while (text[i] != '\0')
    {
        if (isspace(text[i]) && !isspace(text[i + 1]))
        {
            words++;
        }
        i++;
    }
    return words + 1;
}

//function to get the number of sentences in the given text
int count_sentences(string text)
{
    int sentences = 0, i = 0;

    while (text[i] != '\0')
    {
        if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            sentences++;
            i++;
        }
        else
        {
            i++;
        }
    }
    return sentences;
}

//function to print out the grades
void grade(int index)
{
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}