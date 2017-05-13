#include <stdio.h>
#include <cs50.h>

//declare main function
int main(void)
{
    //request length of showers in minutes then save it as n
    printf("Please give me the length of your showers in minutes.\n");
    int n = GetInt();

    //multiply by 12 to get number of bottles of water
    int bottles = 12*n;

    //print number of bottles of water used per shower
    printf("You use %i bottles of water per shower!\n", bottles);
}
