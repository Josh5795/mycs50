#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

//declare main function
int main(void)

{
    //request full name and save answer as string
    string s;
    printf("Please give me your full name.\n");
    s = GetString();

    //if first letter is lowercase change to uppercase
    if(islower(s[0]))
        {
        printf("%c", toupper(s[0]));
        }

    //else keep print it the same
    else
    {
        printf("%c", s[0]);
    }

    //iterate through string
    for (int i = 0; i < strlen(s); i++)
    {
        //if character is a space print the letter after it in uppercase(first letter of each name)
        if (s[i] == ' ')
        {
            printf("%c", toupper(s[i+1]));
        }

    }

    //newline
    printf("\n");
}
