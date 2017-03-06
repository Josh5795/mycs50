#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)

{
    string s;
    printf("Please give me your full name.\n");
    s = GetString();

    if(islower(s[0]))
    {
        printf("%c", toupper(s[0]));
    }

    else
    {
        printf("%c", s[0]);
    }

    for (int i = 0; i < strlen(s); i++)

    {
        if (s[i] == ' ')
        {
            printf("%c", toupper(s[i+1]));
        }

    }

    printf("\n");
}
