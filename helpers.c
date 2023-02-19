#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avg = (float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
            int ravg = round(avg);
            image[i][j].rgbtBlue = ravg;
            image[i][j].rgbtGreen = ravg;
            image[i][j].rgbtRed = ravg;
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
            int originalBlue = image[i][j].rgbtBlue;
            int originalGreen = image[i][j].rgbtGreen;
            int originalRed = image[i][j].rgbtRed;

            int sepiaBlue = round((float)(originalBlue * .131) + (originalGreen * .534) + (originalRed * .272));
            int sepiaGreen = round((float)(originalRed * .349) + (originalGreen * .686) + (originalBlue * .168));
            int sepiaRed = round((float)(originalRed * .393) + (originalGreen * .769) + (originalBlue * .189));

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)         // divid width by 2 because the image reflect will be complete by half way. Going all the way through the row will re-reflect the image to normal.
        {
            RGBTRIPLE tmp = image[i][j];            // set temporary variable to store the rgb values of j pixel in array
            image[i][j] = image[i][width - 1 - j];  // set the j pixel in array to the array-1-j effectively swapping horizontally (array starts at 0 so must use width-1-j)
            image[i][width - 1 -j] = tmp;          // set end pixels to the beginning pixel that was stored in tmp
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // copy array
    RGBTRIPLE og[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            og[i][j] = image[i][j];
        }
    }

    // iterate through array and apply new avg colors
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // First row
            if (i == 0)
            {
                // Top-left corner
                if (j == 0)
                {
                    image[i][j].rgbtRed = round((float)(og[i][j].rgbtRed + og[i + 1][j].rgbtRed + og[i + 1][j + 1].rgbtRed + og[i][j + 1].rgbtRed) / 4);
                    image[i][j].rgbtGreen = round((float)(og[i][j].rgbtGreen + og[i + 1][j].rgbtGreen + og[i + 1][j + 1].rgbtGreen + og[i][j + 1].rgbtGreen) / 4);
                    image[i][j].rgbtBlue = round((float)(og[i][j].rgbtBlue + og[i + 1][j].rgbtBlue + og[i + 1][j + 1].rgbtBlue + og[i][j + 1].rgbtBlue) / 4);
                }
                // Top-right corner
                else if (j == width - 1)
                {
                    image[i][j].rgbtRed = round((float)(og[i][j].rgbtRed + og[i + 1][j].rgbtRed + og[i + 1][j - 1].rgbtRed + og[i][j - 1].rgbtRed) / 4);
                    image[i][j].rgbtGreen = round((float)(og[i][j].rgbtGreen + og[i + 1][j].rgbtGreen + og[i + 1][j - 1].rgbtGreen + og[i][j - 1].rgbtGreen) / 4);
                    image[i][j].rgbtBlue = round((float)(og[i][j].rgbtBlue + og[i + 1][j].rgbtBlue + og[i + 1][j - 1].rgbtBlue + og[i][j - 1].rgbtBlue) / 4);
                }
                // Top row, noncorners
                else
                {
                    image[i][j].rgbtRed = round((float)(og[i][j].rgbtRed + og[i][j - 1].rgbtRed + og[i + 1][j - 1].rgbtRed + og[i + 1][j].rgbtRed + og[i + 1][j + 1].rgbtRed + og[i][j + 1].rgbtRed) / 6);
                    image[i][j].rgbtGreen = round((float)(og[i][j].rgbtGreen + og[i][j - 1].rgbtGreen + og[i + 1][j - 1].rgbtGreen + og[i + 1][j].rgbtGreen + og[i + 1][j + 1].rgbtGreen + og[i][j + 1].rgbtGreen) / 6);
                    image[i][j].rgbtBlue = round((float)(og[i][j].rgbtBlue + og[i][j - 1].rgbtBlue + og[i + 1][j - 1].rgbtBlue + og[i + 1][j].rgbtBlue + og[i + 1][j + 1].rgbtBlue + og[i][j + 1].rgbtBlue) / 6);
                }
            }
            // Last row
            else if (i == height - 1)
            {
                // Bottom-left corner
                if (j == 0)
                {
                    image[i][j].rgbtRed = round((float)(og[i][j].rgbtRed + og[i - 1][j].rgbtRed + og[i - 1][j + 1].rgbtRed + og[i][j + 1].rgbtRed) / 4);
                    image[i][j].rgbtGreen = round((float)(og[i][j].rgbtGreen + og[i - 1][j].rgbtGreen + og[i - 1][j + 1].rgbtGreen + og[i][j + 1].rgbtGreen) / 4);
                    image[i][j].rgbtBlue = round((float)(og[i][j].rgbtBlue + og[i - 1][j].rgbtBlue + og[i - 1][j + 1].rgbtBlue + og[i][j + 1].rgbtBlue) / 4);
                   //printf("%i\n", image[2][0].rgbtRed);
                }
                // Bottom-right corner
                if (j == width - 1)
                {
                    image[i][j].rgbtRed = round((float)(og[i][j].rgbtRed + og[i - 1][j].rgbtRed + og[i - 1][j - 1].rgbtRed +og[i][j - 1].rgbtRed) / 4);
                    image[i][j].rgbtGreen = round((float)(og[i][j].rgbtGreen + og[i - 1][j].rgbtGreen + og[i - 1][j - 1].rgbtGreen +og[i][j - 1].rgbtGreen) / 4);
                    image[i][j].rgbtBlue = round((float)(og[i][j].rgbtBlue + og[i - 1][j].rgbtBlue + og[i - 1][j - 1].rgbtBlue +og[i][j - 1].rgbtBlue) / 4);
                }
                // Bottom row, noncorners
                else if (j != 0)
                {
                    image[i][j].rgbtRed = round((float)(og[i][j].rgbtRed + og[i][j + 1].rgbtRed + og[i - 1][j + 1].rgbtRed + og[i - 1][j].rgbtRed + og[i - 1][j - 1].rgbtRed + og[i][j - 1].rgbtRed) / 6);
                    image[i][j].rgbtGreen = round((float)(og[i][j].rgbtGreen + og[i][j + 1].rgbtGreen + og[i - 1][j + 1].rgbtGreen + og[i - 1][j].rgbtGreen + og[i - 1][j - 1].rgbtGreen + og[i][j - 1].rgbtGreen) / 6);
                    image[i][j].rgbtBlue = round((float)(og[i][j].rgbtBlue + og[i][j + 1].rgbtBlue + og[i - 1][j + 1].rgbtBlue + og[i - 1][j].rgbtBlue + og[i - 1][j - 1].rgbtBlue + og[i][j - 1].rgbtBlue) / 6);
                    //printf("%i\n", image[2][0].rgbtRed);
                }
            }
            // First column, non corners
            else if (i != height - 1 && i != 0 && j == 0)
            {
                image[i][j].rgbtRed = round((float)(og[i][j].rgbtRed + og[i - 1][j].rgbtRed + og[i - 1][j + 1].rgbtRed + og[i][j + 1].rgbtRed + og[i + 1][j + 1].rgbtRed + og[i + 1][j].rgbtRed) / 6);
                image[i][j].rgbtGreen = round((float)(og[i][j].rgbtGreen + og[i - 1][j].rgbtGreen + og[i - 1][j + 1].rgbtGreen + og[i][j + 1].rgbtGreen + og[i + 1][j + 1].rgbtGreen + og[i + 1][j].rgbtGreen) / 6);
                image[i][j].rgbtBlue = round((float)(og[i][j].rgbtBlue + og[i - 1][j].rgbtBlue + og[i - 1][j + 1].rgbtBlue + og[i][j + 1].rgbtBlue + og[i + 1][j + 1].rgbtBlue + og[i + 1][j].rgbtBlue) / 6);
                //printf("%i\n", image[2][0].rgbtRed);
            }
            // Last column, non corners
            else if (j == width - 1)
            {
                image[i][j].rgbtRed = round((float)(og[i][j].rgbtRed + og[i - 1][j].rgbtRed + og[i - 1][j - 1].rgbtRed + og[i][j - 1].rgbtRed + og[i + 1][j - 1].rgbtRed + og[i + 1][j].rgbtRed) / 6);
                image[i][j].rgbtGreen = round((float)(og[i][j].rgbtGreen + og[i - 1][j].rgbtGreen + og[i - 1][j - 1].rgbtGreen + og[i][j - 1].rgbtGreen + og[i + 1][j - 1].rgbtGreen + og[i + 1][j].rgbtGreen) / 6);
                image[i][j].rgbtBlue = round((float)(og[i][j].rgbtBlue + og[i - 1][j].rgbtBlue + og[i - 1][j - 1].rgbtBlue + og[i][j - 1].rgbtBlue + og[i + 1][j - 1].rgbtBlue + og[i + 1][j].rgbtBlue) / 6);
                //printf("%i\n", image[2][0].rgbtRed);
            }
            // Middle body of pixels
            else
            {
                image[i][j].rgbtRed = round((float)(og[i][j].rgbtRed + og[i][j - 1].rgbtRed + og[i][j + 1].rgbtRed + og[i - 1][j].rgbtRed + og[i + 1][j].rgbtRed + og[i - 1][j - 1].rgbtRed + og[i - 1][j + 1].rgbtRed + og[i + 1][j - 1].rgbtRed + og[i + 1][j + 1].rgbtRed) / 9);
                image[i][j].rgbtGreen = round((float)(og[i][j].rgbtGreen + og[i][j - 1].rgbtGreen + og[i][j + 1].rgbtGreen + og[i - 1][j].rgbtGreen + og[i + 1][j].rgbtGreen + og[i - 1][j - 1].rgbtGreen + og[i - 1][j + 1].rgbtGreen + og[i + 1][j - 1].rgbtGreen + og[i + 1][j + 1].rgbtGreen) / 9);
                image[i][j].rgbtBlue = round((float)(og[i][j].rgbtBlue + og[i][j - 1].rgbtBlue + og[i][j + 1].rgbtBlue + og[i - 1][j].rgbtBlue + og[i + 1][j].rgbtBlue + og[i - 1][j - 1].rgbtBlue + og[i - 1][j + 1].rgbtBlue + og[i + 1][j - 1].rgbtBlue + og[i + 1][j + 1].rgbtBlue) / 9);
                //printf("%i\n", image[2][0].rgbtRed);
            }
        }
    }
    return;
}
