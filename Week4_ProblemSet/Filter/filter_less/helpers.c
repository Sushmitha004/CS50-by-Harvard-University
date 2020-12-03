#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round((.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue));
            int sepiaGreen = round((.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue));
            int sepiaBlue = round((.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue));

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            image[i][j].rgbtGreen = sepiaGreen;
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // int start = 0, end = width-1 - j;
            // while (start < end)
            // {
            //temp variables
            int tmpR = image[i][j].rgbtRed;
            int tmpG = image[i][j].rgbtGreen;
            int tmpB = image[i][j].rgbtBlue;
            // opposite end is = width - unit
            //Swap
            image[i][j].rgbtRed = image[i][(width - 1) - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][(width - 1) - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][(width - 1) - j].rgbtBlue;

            image[i][(width - 1) - j].rgbtRed = tmpR;
            image[i][(width - 1) - j].rgbtGreen = tmpG;
            image[i][(width - 1) - j].rgbtBlue = tmpB;

            // temp = image[i][start].rgbtRed;
            // image[i][start].rgbtRed = image[i][end].rgbtRed;
            // image[i][end].rgbtRed = temp;
            // temp = image[i][start].rgbtGreen;
            // image[i][start].rgbtGreen = image[i][end].rgbtGreen;
            // image[i][end].rgbtRed = temp;
            // temp = image[i][start].rgbtBlue;
            // image[i][start].rgbtBlue = image[i][end].rgbtBlue;
            // image[i][end].rgbtBlue = temp;

            // start++;
            // end--;
            // }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int counth = 0;
    int countw = 0;
    for (int a = 0; a <= height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            countw++;
        }
        counth++;
    }
    //Temp arrays
    int tempR[counth][countw];
    int tempG[counth][countw];
    int tempB[counth][countw];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
            {
                tempR[i][j] = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 4.0);
                tempG[i][j] = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j +
                                     1].rgbtGreen) / 4.0);
                tempB[i][j] = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) /
                                    4.0);
            }

            if (i == 0 && j == (width - 1))
            {
                tempR[i][j] = round((image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed) / 4.0);
                tempG[i][j] = round((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i +
                                     1][j].rgbtGreen) / 4.0);
                tempB[i][j] = round((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue) /
                                    4.0);
            }

            if (i == (height - 1) && j == 0)
            {
                tempR[i][j] = round((image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed) / 4.0);
                tempG[i][j] = round((image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j +
                                     1].rgbtGreen) / 4.0);
                tempB[i][j] = round((image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue) /
                                    4.0);
            }

            if (i == (height - 1) && j == (width - 1))
            {
                tempR[i][j] = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed) / 4.0);
                tempG[i][j] = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j -
                                     1].rgbtGreen) / 4.0);
                tempB[i][j] = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue) /
                                    4.0);
            }

            if (i == 0 && (j != 0 && j != width - 1))
            {
                tempR[i][j] = round((image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i
                            + 1][j].rgbtRed
                            + image[i + 1][j + 1].rgbtRed) / 6.0);
                tempG[i][j] = round((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                            image[i + 1][j].rgbtGreen
                            + image[i + 1][j + 1].rgbtGreen) / 6.0);
                tempB[i][j] = round((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                            image[i + 1][j].rgbtBlue
                            + image[i + 1][j + 1].rgbtBlue) / 6.0);
            }

            if (i == height - 1 && (j != 0 && j != width - 1))
            {
                tempR[i][j] = round((image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i
                            - 1][j].rgbtRed
                            + image[i - 1][j + 1].rgbtRed) / 6.0);
                tempG[i][j] = round((image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                            image[i - 1][j].rgbtGreen
                            + image[i - 1][j + 1].rgbtGreen) / 6.0);
                tempB[i][j] = round((image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                            image[i - 1][j].rgbtBlue
                            + image[i - 1][j + 1].rgbtBlue) / 6.0);
            }

            if (j == 0 && (i != 0 && i != height - 1))
            {
                tempR[i][j] = round((image[i - 1][j].rgbtRed + image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                            image[i][j + 1].rgbtRed
                            + image[i + 1][j + 1].rgbtRed) / 6.0);
                tempG[i][j] = round((image[i - 1][j].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                            image[i][j + 1].rgbtGreen
                            + image[i + 1][j + 1].rgbtGreen) / 6.0);
                tempB[i][j] = round((image[i - 1][j].rgbtBlue + image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                            image[i][j + 1].rgbtBlue
                            + image[i + 1][j + 1].rgbtBlue) / 6.0);
            }

            if (j == width - 1 && (i != 0 && i != height - 1))
            {
                tempR[i][j] = round((image[i - 1][j].rgbtRed + image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed +
                            image[i][j - 1].rgbtRed
                            + image[i + 1][j - 1].rgbtRed) / 6.0);
                tempG[i][j] = round((image[i - 1][j].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                            image[i][j - 1].rgbtGreen
                            + image[i + 1][j - 1].rgbtGreen) / 6.0);
                tempB[i][j] = round((image[i - 1][j].rgbtBlue + image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                            image[i][j - 1].rgbtBlue
                            + image[i + 1][j - 1].rgbtBlue) / 6.0);
            }

            if (i != 0 && i != height - 1 && j != 0 && j != width - 1)
            {
                tempR[i][j] = round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed +
                            image[i][j].rgbtRed
                            + image[i][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9.0);
                tempG[i][j] = round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j -
                            1].rgbtGreen + image[i][j].rgbtGreen
                            + image[i][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9.0);
                tempB[i][j] = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j -
                            1].rgbtBlue + image[i][j].rgbtBlue
                            + image[i][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 9.0);
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = tempB[i][j];
            image[i][j].rgbtGreen = tempG[i][j];
            image[i][j].rgbtRed = tempR[i][j];
        }
    }

    return;
}
