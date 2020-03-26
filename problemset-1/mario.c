/*------------------------------\
|  Code (C) 2020 Micah Lindley  |
|   Part of the CS50x course    |
|-------------------------------|
|Do not use this code to cheat! |
\------------------------------*/

#include <cs50.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int height = 0;
    // make sure that user's input is between 1 & 8
    while (!(height > 0 && height <= 8))
    {
        height = get_int("Height: ");
    }
    int width = height;
    // loop through rows
    for (int i = 0; i < height; i++)
    {
        for (int i2 = 0; i2 < width - 1; i2++)
        {
            printf(" ");
        }
        for (int i3 = 0; i3 <= height - width; i3++)
        {
            printf("#");
        }
        printf("\n");
        width -= 1;
    }
}
