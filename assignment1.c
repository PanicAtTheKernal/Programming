/*
Program descrpition: This is an ATM program.  Displays a simple menu that allows users to verify their PIN, change their PIN, how many 
successful and unsuccessful attempts have been made and allow users to exit the program. Complied with visual studio code/With Mircosoft C/C++ complier. OS is Windows 10.
Author: Daniel Kondabarov
Date: 4/11/20
*/
#include <stdio.h>

#define PIN_SIZE 4 
#define USER_INPUT_SIZE 5
#define DIGITS_SIZE 10


int main()
{
    int menu_input = 0;
    char digits[DIGITS_SIZE] = {'0','1','2','3','4','5','6','7','8','9'};
    short user_digit_total = 0;
    short check_PIN = 0;
    char default_PIN[PIN_SIZE] = {'1','2','3','4'};
    unsigned int fail_PIN = 0;
    unsigned int succes_PIN = 0;
    char user_input[USER_INPUT_SIZE];
    char temp_input[USER_INPUT_SIZE];
    int i,j;
    char buffer = '0';

    //This is the main bulk of the program. This repeats until the users enters 4 at the menu.
    do
    {
        //Resets the variable because if the user only inputs non-digits then the scanf won't reasign menu_input 
        menu_input = 0;

        //Prints out the menu
        printf("\n\nWelcome to this ATM mangement program\n");
        printf("1. Verify PIN\n");
        printf("2. Change PIN\n");
        printf("3. PIN logs\n");
        printf("4. Exit Program\n\n");

        printf("Enter a number (Will ignore all non-digits)\n");
        scanf("%d", &menu_input);

        do
        {
            //This stops the program from entering an endless loop or adding characters to other variables
            buffer = getchar();
        }//End do
        while (buffer != '\n');
        //Removes all extra characters from the stdin (Input stream used for scanf) until it reaches the end of the line
        

        //Uses the users input from above to then displays the option they wish to see or displays an error message
        switch (menu_input)
        {
            //Asks the user to enter their PIN then checks if their matches the current stored PIN (Default is 1234).
            case 1:
            {
                //Resets variables for the next cycle
                check_PIN = 0;

                //Asks the user to input their PIN (Will only read the first 4 characters)
                printf("\nEnter your PIN (Will only read the first %d characters)\n", PIN_SIZE);
                scanf("%s", &user_input);

                do
                {
                    //This stops the program from entering an endless loop or adding characters to other variables
                    buffer = getchar();
                }//End do
                //Removes all extra characters from the stdin (Input stream used for scanf) stream until it reaches the end of the line
                while (buffer != '\n');

                //Checks if the users enters more than 5 characters. If they didn't then the last element will be empty. The ASCII code for empty is 0. 
                if (user_input[(USER_INPUT_SIZE - 1)] == 0)
                {
                    //Goes through each character in user_input and checks it to see if the character is the same as in default_PIN 
                    for (i = 0; i < PIN_SIZE; i++)
                    {
                        //If the character matches then it will add one to a varaiable that repersents the total amount of characters that match 
                        if (user_input[i] == default_PIN[i])
                        {
                            check_PIN++;
                        }//End if
                    }//End loop

                    //Checks if the total amount of characters that match is equal to size of the PIN length. 
                    if (check_PIN == PIN_SIZE)
                    {
                        printf("PIN is correct\n");
                        succes_PIN++;
                    }//End if
                    else
                    {
                        printf("PIN is incorrect (PIN must be %d chracters long, the first %d characters must be digits and no spaces)\n", PIN_SIZE, PIN_SIZE);
                        fail_PIN++;
                    }//End else
                    
                }//End if
                else
                {
                    printf("PIN is incorrect (PIN must be %d chracters long)\n", PIN_SIZE);
                    fail_PIN++;
                }//End else

                break;
            }//End Case 1


            case 2:
            {
                //Resets the variable for the next cycle
                user_digit_total = 0;

                //Asks the user to input their PIN (Will only read the first 4 characters)
                printf("\nEnter your new PIN (Will only read the first %d characters)\n", PIN_SIZE);
                scanf("%s", &user_input);

                do
                {
                    //This stops the program from entering an endless loop or adding characters to other variables
                    buffer = getchar();
                }//End do
                //Removes all extra characters from the stdin (Input stream used for scanf) stream until it reaches the end of the line
                while (buffer != '\n');

                //Goes through each character in input
                for ( i = 0; i < PIN_SIZE; i++)
                {
                    //And checks if the input is a digit
                    for ( j = 0; j < DIGITS_SIZE; j++)
                    {
                        //If the character is a digit then add 1 to the user_digit_total.
                        if (user_input[i] == digits[j])
                        {
                            user_digit_total++;
                        }
                    }
                }               

                //Checks if the total amount of digits in the first input matches the size of the PIN. ie if there's 4 digits in the input and the PIN_SIZE is 4 then if will be true.
                if (user_digit_total == PIN_SIZE)
                {
                    //Resets the variable for the next cycle
                    user_digit_total = 0;

                    //Asks the user to re-enter their PIN (Will only read the first 4 characters)
                    printf("\nRe-enter your new PIN (Will only read the first %d characters)\n", PIN_SIZE);
                    scanf("%s", &temp_input);

                    do
                    {
                        //This just takes the extra characters to stop the program from entering an endless loop
                        buffer = getchar();
                    }//End do
                    //Removes all extra characters from the stdin (Input stream used for scanf) stream until it reaches the end of the line
                    while (buffer != '\n');

                    //Goes through each character in input 
                    for ( i = 0; i < PIN_SIZE; i++)
                    {
                        //And checks if the input is a digit
                        for ( j = 0; j < DIGITS_SIZE; j++)
                        {
                            //If the character is a digit then add 1 to the user_digit_total.
                            if (temp_input[i] == digits[j])
                            {
                                user_digit_total++;
                            }
                        }
                    }

                    //Checks if the amount of digits in the second input matches the size of the PIN
                    if (user_digit_total == PIN_SIZE)
                    {
                        //Resets variables for the next cycle
                        check_PIN = 0;

                        for (i = 0; i < PIN_SIZE; i++)
                        {
                            //Checks if each character matches, then add that to a total of matching characters 
                            if (user_input[i] == temp_input[i])
                            {
                                check_PIN++;
                            }//End if
                            
                        }//End for

                        //If all the charcter match then the total will be the size of the PIN, then it updates the PIN with the new PIN
                        if (check_PIN == PIN_SIZE)
                        {
                            for (i = 0; i < PIN_SIZE; i++)
                            {
                                //Replaces the character in default_PIN with the new character, thus updating the PIN
                                default_PIN[i] = user_input[i];
                            }
                            
                            printf("Your PIN has been succesfully updated\n");
                        }//End if
                        else
                        {
                            printf("Your PINS do not match. Your PIN remains the same\n");
                        }//End else

                    }//End if
                    else
                    {
                        printf("Your second input must contain %d digits (No spaces or characters)\n", PIN_SIZE);
                    }//End else

                }//End if
                else
                {
                    printf("Your first input must contain %d digits (No spaces or characters)\n", PIN_SIZE);
                }//End else          
                                
                break;
            }//End case 2

            //Tells the user how many times the user has successfully and failed to input their PIN
            case 3:
            {
                //%u is the delimeter for unsigned int
                printf("\nYou have successfully entered your PIN %u times\n", succes_PIN);
                printf("You have failed to entered your PIN %u times\n", fail_PIN);
                break;
            }//End case 3

            //Exits the loop which then exits the programs
            case 4:
            {
                printf("Thank you for you using this software");
                break;
            }//End case 4

            //If the user enters an option thats not on the menu then this message will play
            default:
            {
                printf("Invaild option, try again!\n");
                break;
            }//End default

        }//End switch

    }//End do 
    while (menu_input != 4);
    
    return 0;
}//End main