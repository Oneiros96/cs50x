#include "helpers.h"
#include "math.h"


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //for evry row...
    for (int row = 0, max_row = height; row < max_row; row++)
    {
        //...and evry columm in that row
        for (int columm = 0, max_columm = width; columm < max_columm; columm++)
        {

            RGBTRIPLE current_pixel = image[row][columm];
            //rounding isues when using image.[row][columm] direktly
            //sets average to the average colour value of the current pixel
            int average = round((current_pixel.rgbtBlue + current_pixel.rgbtRed + current_pixel.rgbtGreen) / 3.0);
            //replace current pixel colour value's with there average value to get a tone of gray
            image[row][columm].rgbtBlue = average;
            image[row][columm].rgbtRed = average;
            image[row][columm].rgbtGreen = average;
        }

    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0, max_row = height; row < max_row; row++)
    {
        //temp memory of curent row
        RGBTRIPLE temp[width];
        for (int columm = 0, max_columm = width; columm < max_columm; columm++)
        {
            //fills temp row backwards to mirror input image
            temp[width - columm - 1] = image[row][columm];
        }
        for (int columm = 0, max_columm = width; columm < max_columm; columm++)
        {
            //output of mirrored row
            image[row][columm] = temp[columm];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //storage for temporary image
    RGBTRIPLE temp_image[height][width];
    //for evry row...
    for (int row = 0, max_row = height; row < max_row; row++)
    {
        //...and evry columm in that row - > generate temp image
        for (int columm = 0, max_columm = width; columm < max_columm; columm++)
        {
            int surrounding_pixels = 0;
            float average_blue = 0, average_red = 0, average_green = 0;
            //matrix for looking at each pixel in a 3x3 square arround current pixel with nested for loops i & j
            int temp_row[]  = {row - 1, row, row + 1};
            int temp_columm[] = {columm - 1, columm, columm + 1};
            //adds clolour values of surrounding pixels
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (temp_row[i] >= 0 && temp_row[i] < max_row && temp_columm[j] >= 0 && temp_columm[j] < width)
                    {
                        average_blue = average_blue + image[temp_row[i]][temp_columm[j]].rgbtBlue;
                        average_red = average_red + image[temp_row[i]][temp_columm[j]].rgbtRed;
                        average_green = average_green + image[temp_row[i]][temp_columm[j]].rgbtGreen;
                        surrounding_pixels++;
                    }
                }
            }
            //sets pixel to the average value of surrounding pixels
            temp_image[row][columm].rgbtBlue = round(average_blue / surrounding_pixels);
            temp_image[row][columm].rgbtRed = round(average_red / surrounding_pixels);
            temp_image[row][columm].rgbtGreen = round(average_green / surrounding_pixels);
        }
    }
    //for evry row...
    for (int row = 0, max_row = height; row < max_row; row++)
    {
        //...and evry columm in that row - > copy temp to image
        for (int columm = 0, max_columm = width; columm < max_columm; columm++)
        {
            image[row][columm] = temp_image[row][columm];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //storage for temp image
    RGBTRIPLE temp_image[height][width];
    //matrixes for edges algorithm
    int gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0,},
        {1, 2, 1}
    };
    //for evry pixel of the image
    for (int row = 0, max_row = height; row < max_row; row++)
    {
        for (int columm = 0, max_columm = width; columm < max_columm; columm++)
        {
            //temp values for active pixel
            float gx_blue = 0, gx_red = 0, gx_green = 0, gy_blue = 0, gy_red = 0, gy_green = 0;
            int final_blue = 0, final_red = 0, final_green = 0;

            //same funktion like for boxblur
            int temp_row[]  = {row - 1, row, row + 1};
            int temp_columm[] = {columm - 1, columm, columm + 1};
            for (int i = 0; i < 3; i++)
            {

                for (int j = 0; j < 3; j++)
                {
                    //if pixel doesn't exist pixel value = 0 -> kann be ignored
                    if (temp_row[i] >= 0 && temp_row[i] < max_row && temp_columm[j] >= 0 && temp_columm[j] < width)
                    {
                        //get value of surrounding pixels of aktive pixel for evry colourchannel mutiplying them by shema of matrixes gx & gy
                        gx_blue = gx_blue + (image[temp_row[i]][temp_columm[j]].rgbtBlue * gx[i][j]);
                        gx_red = gx_red + (image[temp_row[i]][temp_columm[j]].rgbtRed * gx[i][j]);
                        gx_green = gx_green + (image[temp_row[i]][temp_columm[j]].rgbtGreen * gx[i][j]);
                        gy_blue = gy_blue + (image[temp_row[i]][temp_columm[j]].rgbtBlue * gy[i][j]);
                        gy_red = gy_red + (image[temp_row[i]][temp_columm[j]].rgbtRed * gy[i][j]);
                        gy_green = gy_green + (image[temp_row[i]][temp_columm[j]].rgbtGreen * gy[i][j]);
                    }
                }
            }
            //out of "boxblur" loop
            //final rgb = √(gx²+gy²)
            final_blue = round(sqrt((gx_blue * gx_blue) + (gy_blue * gy_blue)));
            final_red = round(sqrt((gx_red * gx_red) + (gy_red * gy_red)));
            final_green = round(sqrt((gx_green * gx_green) + (gy_green * gy_green)));
            //set them 255 if they are larger
            if (final_blue > 255)
            {
                final_blue = 255;
            }
            if (final_red > 255)
            {
                final_red = 255;
            }
            if (final_green > 255)
            {
                final_green = 255;
            }
            //write final value to temp image
            temp_image[row][columm].rgbtBlue = final_blue;
            temp_image[row][columm].rgbtRed = final_red;
            temp_image[row][columm].rgbtGreen = final_green;
        }
    }
    //ouf of loops for individual pixels
    //for evry row...
    for (int row = 0, max_row = height; row < max_row; row++)
    {
        //...and evry columm in that row - > copy temp to image
        for (int columm = 0, max_columm = width; columm < max_columm; columm++)
        {
            image[row][columm] = temp_image[row][columm];
        }
    }
    return;
}
