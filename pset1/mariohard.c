#include <stdio.h>
#include <cs50.h>

//declaring main function
int main(void)

{
    int height;

    //print request for height and save it using get int repeat until height is between 0 and 23
    do
    {
      printf("Please give me a non-negative integer less than or equal to 23.\n");
      height = GetInt();
    }
    while(height < 0 || height > 23);

    //for each row
    for(int i = 0; i < height; i++)
    {
        //print spaces before first half pyramid
        for(int j = 0; j < height-i-1; j++)
        {
            printf(" ");
        }

        //print hashes of first half pyramid
        for(int k = 0; k < i+1; k++)
        {
            printf("#");
        }

    //print gap between two half pyramids
    printf("  ");

        //print hashes for second half pyramid
        for(int k = 0; k < i+1; k++)
        {
            printf("#");
        }

    //new line
    printf("\n");
    }

}
