/*------------------------------\
|  Code (C) 2020 Micah Lindley  |
|   Part of the CS50x course    |
|-------------------------------|
|Do not use this code to cheat! |
\------------------------------*/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");
    float index = 0;
    int length = strlen(text);
    float sentances = 0;
    float words = 1;
    float chars = 0;
    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i]))
        {
            chars++;
        }
        else if (text[i] == ' ')
        {
            words++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            i += 2;
            sentances++;
        }
    }
    float l = (100 * (float) chars / (float) words);
    float s = (100 * (float) sentances / (float) words);
    index = 0.0588 * l - 0.296 * s - 15.8;
    int indexAsInt = round(index);
    if (indexAsInt >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (indexAsInt < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", indexAsInt);
    }
}
