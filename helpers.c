 #include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; ++h)
    {
        for (int w = 0; w < width; ++w)
        {
            //TODO
            //Calculate the average pixel value
            float n = (image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed);
            n /= 3;

            //set each colour value to the average value
            image[h][w].rgbtBlue = round(n);
            image[h][w].rgbtGreen = round(n);
            image[h][w].rgbtRed = round(n);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //for each pixel
    for (int h = 0; h < height; ++h)
    {
        for (int w = 0; w < width; ++w)
        {
            //calculate each new colour value using the sepia formula
            float R = ((.393 * image[h][w].rgbtRed) + (.769 * image[h][w].rgbtGreen) + (.189 * image[h][w].rgbtBlue));
            float G = ((.349 * image[h][w].rgbtRed) + (.686 * image[h][w].rgbtGreen) + (.168 * image[h][w].rgbtBlue));
            float B = ((.272 * image[h][w].rgbtRed) + (.534 * image[h][w].rgbtGreen) + (.131 * image[h][w].rgbtBlue));
            
            //cap the values of R, G, B between 0 - 255 inclusively
            if (R > 255)
            {
                R = 255;
            }
            if (G > 255)
            {
                G = 255;
            }
            if (B > 255)
            {
                B = 255;
            }
            
            // //round to the nearest integer while assigning the values of RGB into the colour value
            image[h][w].rgbtRed = round(R);
            image[h][w].rgbtGreen = round(G);
            image[h][w].rgbtBlue = round(B);
        
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2; w++)
        {
            RGBTRIPLE temp = image[h][w];
            image[h][w] = image[h][width - 1 - w];
            image[h][width - 1 - w] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // new image to work on then later swap to original image 
    RGBTRIPLE temp[height][width];

    // iterate over Row
    for (int h = 0; h < height; h++)
    {
        // iterate over each pixels left to right
        for (int w = 0; w < width; w++)
        {
            // Reset values after each cycle over a pixel
            float Red = 0, Green = 0, Blue = 0;
            int counter == 0;

            // iterate on corresponding 3x3 block using 2 for loops to determine avg
            for (int m = h - 1; m <= h + 1; m++)
            {
                for (int n = w - 1; n <= w + 1; n++)
                {
                    // Condition to check corners of img and to avoid non pixels being added in avg.
                    if (!(m < 0 || m > (height - 1) || n < 0 || n > (width - 1))) // corner cases
                    {
                        Red += image[m][n].rgbtRed;
                        Green += image[m][n].rgbtGreen;
                        Blue += image[m][n].rgbtBlue;
                        counter++;
                    }
                }     
            } 
            temp[h][w].rgbtRed = round(Red / counter);
            temp[h][w].rgbtGreen = round(Green / counter);
            temp[h][w].rgbtBlue = round(Blue / counter);
        }
    }
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < height; w++)
        {
            image[h][w].rgbtRed = temp[h][w].rgbtRed;
            image[h][w].rgbtGreen = temp[h][w].rgbtGreen; 
            image[h][w].rgbtBlue = temp[h][w].rgbtBlue;
        }
    }
    return;
}
