#include <cs50.h>
#include <stdio.h>

int main(void)

{
    float d;
    do
    {
        printf("Please give the amount of change owed in dollars.\n");
        d = GetFloat();
    }
    while (d < 0);

    int c;
    {
        c = 100*d;
        printf("That's %i in cents.\n", c);
    }

    int n = 0;

    for (; c >= 25 ; c = c - 25)
    {
        n++;
    }

    for (; c >= 10; c = c - 10)
    {
        n++;
    }

    for (; c >= 5; c = c - 5)
    {
        n++;
    }

    for (; c >= 1; c = c - 1)
    {
        n++;
    }

    printf("Number of coins: %i\n", n);

}
