#include <cs50.h>
#include <stdio.h>

//declaring main function
int main(void)

{
    //declare float variable which will be amount of change owed in dollars
    float d;

    //saving the amount of change owed as d
    do
    {
        printf("Please give the amount of change owed in dollars.\n");
        d = GetFloat();
    }
    while(d < 0);

    //covert change owed from dollars into cents and print it
    int c;
    {
        c = 100*d;
        printf("That's %i in cents.\n", c);
    }

    //initialise n as 0
    int n = 0;

    //if cents (c) is greater than or equal to 25
    //add one to number of coins (n)
    //subtract 25 from c
    //repeat until c is less than 25
    for (; c >= 25 ; c = c - 25)
    {
        n++;
    }

    //if c is between 10 and 24 inclusive
    //add one to n
    //subtract 10 from c
    //repeat until c is less than 10
    for (; c >= 10; c = c - 10)
    {
        n++;
    }

    //if c is between 5 and 9 inclusive
    //add one to n
    //subtract 5 from c
    //repeat until c is less than 5
    for (; c >= 5; c = c - 5)
    {
        n++;
    }

     //if c is between 1 and 4 inclusive
    //add one to n
    //subtract 1 from c
    // repeat until c is 0
    for (; c >= 1; c = c - 1)
    {
        n++;
    }

   //print number of coins
    printf("Number of coins: %i\n", n);

}
