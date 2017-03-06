/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

#include <stdio.h>
/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{

//binary search
int start = 0;
int end = n-1;
int lengthofarray = (end-start);
int midpoint;

//while length of array(or subarray) is > 0
while (lengthofarray >= 0)
{
    //calculate midpoint of current array
    if (lengthofarray % 2 == 1)
    {
        midpoint = ((lengthofarray-1)/2)+start;
    }

    if (lengthofarray % 2 == 0)
    {
        midpoint = (lengthofarray/2)+start;
    }

    //if midpoint is number looking for, return true (+ you found it)
    if (value == values[midpoint])
    {
        printf("You found %i!", value);
        return true;
    }
     //if number you're looking for is greater than midpoint, change first number of array to just right of midpoint.
    if (value > values[midpoint])
    {
        start = midpoint + 1;
    }
    //if number you're looking for is less than midpoint, change last number of array to just left of midpoint.
    if (value < values[midpoint])
    {
        end = midpoint - 1;
    }
    lengthofarray = (end-start);
}
printf("You didn't find %i!", value);
return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{


//selection sort:
//for i = 0 to n-2
for(int i = 0; i < n-1; i++)
{
    int smallest = values[i];
    int indexofsmallest = i;
    //find the smallest element from i+1 to n-1
    for (int j=i+1; j < n; j++)
    {
        if(values[j]<smallest)
        {
            //exchange smallest element with element at i
            smallest = values[j];
            indexofsmallest = j;
        }

    }
   int temp = values[i];
   values[i] = values[indexofsmallest];
   values[indexofsmallest] = temp;
}
}
