#include <stdio.h>
#include <cs50.h>

int main(void)
{
    {
    printf("Please give me the length of your showers in minutes.\n");
    int n = GetInt();
    int bottles = 12*n;
    printf("You use %i bottles of water per shower!\n", bottles);
    }
}
