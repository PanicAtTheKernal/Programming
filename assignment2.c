/*
Program descrpition: This program allows the user to enter a code. Then the user can encrypt that code and check to see if the code matches the access code. 
The user can also decrypt the code. The progarm allows the user to see how many time the code has been input correctly and incorrectly
Author: Daniel Kondabarov
Date: 21/2/21
*/
#include <stdio.h>

#define SIZE 4

int code_input(int*);
int encrypt_code(int*,int*,int*);
int decrypt_code(int*);
void input_rate(char*);
int exit_prog();

int main()
{
    int access_code[SIZE] = {4,5,2,3};
    int user_code[SIZE] = {0,0,0,0};
    int user_input = 0;
    char menu_char = 'p';
    int status = 0;
    int end_prog = 0;
    char temp;

    //This main loop runs until the user decides to exit the program
    do
    {
        //Resets the variable for the next cycle 
        user_input = 0;

        //Prints the main menu
        printf("1.Enter any code\n");
        printf("2.Encrypt code entered and verify if correct\n");
        printf("3.Decrypt code\n");
        printf("4,Display the number of times the encrypted code entered matches the authorised code successfully and incorrectly\n");
        printf("5.Exit program\n");        
        scanf("%d", &user_input);

        //Removes extra character form the input buffer
        do
        {
            temp = getchar();
        } 
        while (temp != '\n');
        //End do while

        //This switch triggers the correct function corresponding to the menu item. I.e Users inputs one then the "code_input" functon triggers.
        switch (user_input)
        {
            //This is for code input
            case 1:
            {
                status = code_input(user_code);  
                break;
            }//End case 1

            //This is for encrypting the code
            case 2:
            {
                //This only allow the user to encrypt their code if it's 1(The user enters a code) or 3(The user decrypts thier code)
                if (status == 1 || status == 3)
                {
                    status = encrypt_code(user_code,access_code,&status);
                }//End if
                else
                {
                    printf("You must enter a code or use a decrypted code\n");
                }//End else
                break;
            }//End case 2

            //This for decrypting the code
            case 3:
            {
                //This will only allow the user to decrypt their code if it's 2(The code is encrypted)
                if (status == 2)
                {
                    status = decrypt_code(user_code);
                }//End if
                else
                {
                    printf("The code must be encrypted before you can decrypt it\n");
                }//End else
                break;
            }//End case 3

            //This is for showing how many times the user enter the correct code or not
            case 4:
            {
                input_rate(&menu_char);
                break;
            }//End case 4

            //This promts the user if they want to exit
            case 5:
            {
                end_prog = exit_prog();
                break;
            }//End case 5

            //This is for when the user enters a number thats not on the menu
            default:
            {
                printf("Your input is invaild\n");
                break;
            }//End default
        }//End Switch
    } 
    while (end_prog != 1);
    //End do while

    return 0;
}//End main

//This function enters values for the user_code
int code_input(int *parm_user)
{
    char temp;
    //-1 represent invaild input. When the user inputs a character instead of a digit, user_input will still be -1. With this knowledge, the apporative error will display
    int user_input = -1;
    int is_vaild_input = 0;

    //This for loop is to get the values for the user_code
    for (int i = 0; i < SIZE; i++)
    {
        //Resets the variable for the next loop cycle
        is_vaild_input = 0;

        //This loop repeats untill the user enters a digit between 0 and 9
        do
        {
            printf("Enter digit %d of your code (Non-digits will be ingored)\n", i);
            scanf("%d", &user_input);

            //This checks if the user input is between 0 and 9, if it is between 0 and 9 it will add that digit to the array
            if (user_input > -1 && user_input < 10)
            {
                *(parm_user + i) = user_input;
                //Resets the variable for the next loop cycle
                user_input = -1;
                is_vaild_input = 1;
            }//End if
            else
            {
                printf("\n Number must be between 0 and 9\n");
            }//End else
            
            //This loop removes the charcters from the buffer
            do
            {
                temp = getchar();
            } while (temp != '\n');
            //End do while

        } 
        while (is_vaild_input != 1);
        //End do while
        
    }//End for
    
    return 1;
}//End code_input

//This function encrypts the user code and then compares it to the access code. If the code matches or not it will trigger a function to add those numbers
int encrypt_code(int *pram_user, int *pram_code,int *status)
{
    int temp;
    int i;
    int matching_nums = 0;
    char selector;

    //This switches around digit 0 with digit 2
    temp = *(pram_user);
    *(pram_user) = *(pram_user + 2);
    *(pram_user + 2) = temp; 

    //This switches around digit 1 with digit 3
    temp = *(pram_user + 1);
    *(pram_user + 1) = *(pram_user + 3);
    *(pram_user + 3) = temp;

    //This adds 1 to every value in pram_user then mods 10 to make sure the number is less than 10
    for (i = 0; i < SIZE; i++)
    {
        *(pram_user + i) = (*(pram_user + i) + 1) % 10;   
    }//End for
    
    //This goes throught every number in the user_code and compares it with the access_code 
    for (i = 0; i < SIZE; i++)
    {
        //If the digit matches it add 1 to a total
        if (*(pram_user + i) == *(pram_code + i))
        {
            matching_nums++;
        }//End if
    }//End for
    
    //The amount of times a code is correct or not is only done when there is a new new code. A decrypted code won't go towards the total amount of times
    if (*(status) == 1)
    {
        //If matching_num equals to the length of the code then the user_code matchs the access_code
        if (matching_nums == SIZE)
        {
            //Success case
            printf("\nCorrect Code entered\n");
            selector = 's';
            input_rate(&selector);
        }//End if
        else
        {
            //Failure case
            printf("\nWrong Code entered\n");
            selector = 'f';
            input_rate(&selector);
        }//End else
    }//End if
    
    
    printf("Your code has been encrypted\n\n");

    return 2;
}//End encrypt_code

//This function dycrypts the code from an encrypted code
int decrypt_code(int *pram_user)
{
    int i;
    int temp;

    //Goes through each digit in the code and subtract 1 from it
    for (i = 0; i < SIZE; i++)
    {
        *(pram_user + i) = *(pram_user + i) - 1;

        //If the value is less than 0 then set the value to 9
        if (*(pram_user+ i) < 0)
        {
            *(pram_user+ i) = 9;
        }//End if
        
    }//End for
    
    //This switches around digit 0 with digit 2
    temp = *(pram_user);
    *(pram_user) = *(pram_user + 2);
    *(pram_user + 2) = temp; 

    //This switches around digit 1 with digit 3
    temp = *(pram_user + 1);
    *(pram_user + 1) = *(pram_user + 3);
    *(pram_user + 3) = temp;

    printf("Your code has been decrypted\n\n");

    return 3;
}//End decrypt_code

//This function displays and adds values to amount of times the code has been submited correctly and incorrectly. 's' adds one to succes, 'f' adds one to failure, 'p' prints out success and failure
void input_rate(char *selector)
{
    static int success = 0;
    static int failure = 0;

    //This switch does different things based on the value of the paramter passed through 
    switch (*(selector))
    {
        //Adds one to success meaning the code has been entered correctly 
        case 's':
        {
            success++;
            break;
        }//End case 's'

        //Add one to failure meaning the code has been entered incorrectly
        case 'f':
        {
            failure++;
            break;
        }//End case 'f'

        //Print how many times the user has entered the code correctly and incorrectly
        case 'p':
        {
            printf("\nThe code has been entered successfully %d\n", success);
            printf("\nThe code has been entered incorrectly %d\n\n", failure);
            break;
        }//End case 'p'

        //Defualt won't be called unless the function was called incorretly
        default:
        {
            break;
        }//End default
    }//End Switch

    return;
}//End input_rate

//This asks the user to confirm that they want to exit the program, it will return 1 to exit the program, 0 to stay in the program
int exit_prog()
{
    char confirm = 'a';
    char temp;

    //This loop repeats untill the user enters a 'y' or 'n'
    do
    {
        printf("Do you want to exit? y for yes, n for no\n");
        scanf("%1s", &confirm);

        //Removes extra characters from the buffer
        do
        {
            temp = getchar();
        } 
        while (temp != '\n');
        //End do while
        
        //This checks that the user enters a character and return a certain value. 1 exits the program and 0 stays in the program
        if (confirm == 'y')
        {
            return 1;
        }//End if
        else if (confirm == 'n')
        {
            return 0;
        }//End else if
        else
        {
            printf("\nInvaild character\n");
        }//End else
        
        
    } 
    while (confirm != 'y' || confirm != 'n');
    //End do while

    return 0;
}//End exit_prog