/*------------------------------\
|  Code (C) 2020 Micah Lindley  |
|   Part of the CS50x course    |
|-------------------------------|
|Do not use this code to cheat! |
\------------------------------*/

#include "helpers.h"
#include <math.h>
#include <unistd.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through rows
    for (int i = 0; i < height; i++)
    {
        // loop through columns
        for (int j = 0; j < width; j++)
        {
            // find average of pixel values
            float avg = ((float) image[i][j].rgbtRed + (float) image[i][j].rgbtGreen + (float) image[i][j].rgbtBlue) / 3;
            // set new pixel values
            image[i][j].rgbtRed = round(avg);
            image[i][j].rgbtGreen = round(avg);
            image[i][j].rgbtBlue = round(avg);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through rows
    for (int i = 0; i < height; i++)
    {
        // loop through columns
        for (int j = 0; j < width; j++)
        {
            // use the sepia algorithm to generate new values
            float sepiaRed = .393 * (float) image[i][j].rgbtRed + .769 * (float) image[i][j].rgbtGreen + .189 * (float) image[i][j].rgbtBlue;
            float sepiaGreen = .349 * (float) image[i][j].rgbtRed + .686 * (float) image[i][j].rgbtGreen + .168 * (float) image[i][j].rgbtBlue;
            float sepiaBlue = .272 * (float) image[i][j].rgbtRed + .534 * (float) image[i][j].rgbtGreen + .131 * (float) image[i][j].rgbtBlue;
            // handle values larger than 24 bits
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            // set new pixel values
            image[i][j].rgbtRed = round(sepiaRed);
            image[i][j].rgbtGreen = round(sepiaGreen);
            image[i][j].rgbtBlue = round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    // loop through row
    for (int i = 0; i < height; i++)
    {
        // loop through columns
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtRed = image[i][(width - j) - 1].rgbtRed;
            temp[i][j].rgbtGreen = image[i][(width - j) - 1].rgbtGreen;
            temp[i][j].rgbtBlue = image[i][(width - j) - 1].rgbtBlue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        // loop through columns
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // make a temporary image array to store intermediate values
    RGBTRIPLE temp[height][width];
    // loop through rows
    for (int y = 0; y < height; y++)
    {
        // loop through columns
        for (int x = 0; x < width; x++)
        {
            // initialize new RGB values
            int r = 0;
            int g = 0;
            int b = 0;
            int pixelCount = 0;
            for (int h = y - 1; h <= y + 1; h++)
            {
                for (int w = x - 1; w <= x + 1; w++)
                {
                    // we have now accessed the pixel to take the average of
                    // check that the pixel is within the image range
                    if ((h >= 0 && w >= 0) && (h < height && w < width))
                    {
                        // set RGB values from original image
                        r += image[h][w].rgbtRed;
                        g += image[h][w].rgbtGreen;
                        b += image[h][w].rgbtBlue;
                        // increase number of pixels scanned for avg
                        pixelCount++;
                    }
                }
            }
            // round RGB values with number of scanned pixels
            r = round((float) r / (float) pixelCount);
            g = round((float) g / (float) pixelCount);
            b = round((float) b / (float) pixelCount);
            // ensure that values are in the correct 0-255 range
            if (r > 255)
            {
                r = 255;
            }
            if (g > 255)
            {
                g = 255;
            }
            if (b > 255)
            {
                b = 255;
            }
            // fill in temporary array with new RGB values
            temp[y][x].rgbtRed = r;
            temp[y][x].rgbtGreen = g;
            temp[y][x].rgbtBlue = b;
        }
    }
    // loop through rows
    for (int y = 0; y < height; y++)
    {
        // loop through columns
        for (int x = 0; x < width; x++)
        {
            // fill in values from temporary array into image
            image[y][x].rgbtRed = temp[y][x].rgbtRed;
            image[y][x].rgbtGreen = temp[y][x].rgbtGreen;
            image[y][x].rgbtBlue = temp[y][x].rgbtBlue;
        }
    }
    return;
}
