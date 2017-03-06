#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// declare command line argument variables
int main(int argc, string argv[])
{

//return error if there aren't two command line arguments
if (argc != 2)
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }

//assign argv[1] as a string called k
string k = argv[1];

//make sure key is all alphabetical
for (int i = 0; i < strlen(k); i++)

  {
    if(!isalpha(k[i]))
    {
        printf("Please ensure all characters are alphabetical.\n");
        return 1;
    }
  }

// get plaintext from user
printf("Plaintext: ");
string p = GetString();

//formatting for where cipher text will be displayed
printf("Ciphertext: ");

//declare lth letter variable
int l = 0;

//iterate through plaintext
for (int j = 0; j < strlen(p); j++)

{

    //make sure the characters of plaintext we are ciphering are alphabetical
    if(isalpha(p[j]))

    {

        //cipher specific to uppercase letters in p
        if(isupper(p[j]))
        {
            //cipher specific to uppercase letters in k
            if(isupper(k[l%strlen(k)]))
            {
              char c1;
              c1 = (((p[j] - 65 + (k[l%strlen(k)]-65))%26)+65);
              printf("%c", c1);
              l++;
            }

            //cipher specific to lowercase letters in k
            else if(islower(k[l%strlen(k)]))
            {
              char c2;
              c2 = (((p[j] - 65 + (k[l%strlen(k)]-97))%26)+65);
              printf("%c", c2);
              l++;
            }
        }

         //cipher specific to lowercase letters in p
        else if(islower(p[j]))
        {
            //cipher specific to uppercase letters in k
            if(isupper(k[l%strlen(k)]))
            {
                char c3;
                c3 = (((p[j] - 97 + (k[l%strlen(k)]-65))%26)+97);
                printf("%c", c3);
                l++;
            }

            //cipher specific to lowercase letters in k
            else if(islower(k[l%strlen(k)]))
            {
                char c4;
                c4 = (((p[j] - 97 + (k[l%strlen(k)]-97))%26)+97);
                printf("%c", c4);
                l++;
            }
        }
    }


    //if not alphabetical print the character as normal
    else
    {
        printf("%c", p[j]);
    }

}

//print new line at end
printf("\n");

}
