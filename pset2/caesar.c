#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// declare command line argument variables
int main(int argc, string argv[])
{

//get key from user in the form of second command line argument after the program name and convert from string to integer value
int k;
k = atoi(argv[1]);

//return error if there aren't two command line arguments
if (argc != 2)
    {
        printf("Incorrect command-line argument.\n");
        return 1;
    }

// get plaintext from user
printf("Plaintext: ");
string s = GetString();

printf("Ciphertext: ");

//iterate through plaintext
for (int i = 0; i < strlen(s); i++)

{
    //make sure the characters of plaintext we are ciphering are alphabetical
    if(isalpha(s[i]))
    {

        //cipher specific to uppercase letters
        if(isupper(s[i]))
        {

            char c1;
            c1 = ((s[i] - 65 + k)%26)+65;
            printf("%c", c1);

        }

        //cipher specific to lowercase letters
        if(islower(s[i]))
        {

            char c2;
            c2 = ((s[i] - 97 + k)%26)+97;
            printf("%c", c2);

        }


    }
    //if not alphabetical print the character as normal
    else
    {
        printf("%c", s[i]);
    }


}
//print new line at end
printf("\n");

}
