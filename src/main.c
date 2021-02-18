#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXL 100
//Function
void multiplication();

int main()
{
    int ch;

    while(1)
    {
        printf("\n*************** Multiplication ***************\n\n");

        printf("1. Multiplication\n");
        printf("0. Exit\n\n");

        puts("**********************************************");

        printf("Please choose an action: ");
        scanf(" %d", &ch);

        switch(ch)
        {
            case 1: multiplication();
            break;
            case 0: exit(0); // Terminates the process
        }
    }

    return 0;
}

void multiplication()
{
    char n1[MAXL+1]; // Plus one is for null operator!
    memset(n1, 0, MAXL*sizeof(char));
    char n2[MAXL+1];
    memset(n2, 0, MAXL*sizeof(char));

    // use sample numbers or input numbers as string
    char choice;
    printf("Do you want to use sample numbers?\n"
           "~~~> Yes: y/Y\n"
           "~~~> No: n/N\n"
           "Your choice:");
    scanf(" %c", &choice);

    if (choice == 'n' || choice =='N') // Enter numbers that you want
    {
        printf("Please enter the first number:\n");
        scanf(" %s", n1);
        printf("Please enter the second number:\n");
        scanf(" %s", n2);
    }
    else if (choice == 'y' || choice == 'Y')
    {
        // Sample numbers
        strcpy(n1, "11111111111111111111111111111111111111111111111122");
        strcpy(n2, "00000000000000000000000000000000000000000000000012");

        printf("\n-----------------Sample numbers-----------------\n");
        printf("%s\n", n1);
        printf("%s\n", n2);
        printf("\n------------------------------------------------\n");
    }
    else
    {
        //return 0;
		 printf("\n-------wrongggggggggggggg--------------\n");
    }

    // Put the longer number first
    char temp[MAXL];
    if (strlen(n1) < strlen(n2))
    {
        strcpy(temp, n1);
        strcpy(n1, n2);
        strcpy(n2, temp);
    }

    // Length of numbers
    int L1 = strlen(n1);
    int L2 = strlen(n2);

    int n=0, m;
    int lent = 2*L1 ; // The resultant number length is at most 2 times the first number.
    int carry=0, summ=0;

    // steps of calculation, like using pen and paper
    int step[L2][lent];
    memset(step, 0, L2*lent*sizeof(int));
    // answer will be stored in result
    int result[lent];
    memset(step, 0, lent*sizeof(int));

    // String of numbers to integer numbers
    int num1[L1];
    int num2[L2];
    for (int i=0; i<L1; i++)
    {
        num1[i] = n1[i] - '0'; // Converts char to integer
    }
    for (int i=0; i<L2; i++)
    {
        num2[i] = n2[i] - '0'; // Converts char to integer
    }

    // Multiplication by algorithm.
    for (int i=L2-1; i>=0; i--)
    {
        m = lent-1;
        for (int j=L1-1; j>=0; j--)
        {
            step[n][m] = (carry + (num2[i] * num1[j])) % 10;
            carry = (carry + num2[i] * num1[j]) / 10;
            m --;

            if (m==lent-L1-1 && carry != 0) // L1 digits are passed. is there still carry? if yes insert it.
            {
                step[n][m] = carry;
                carry=0;
            }
        }
        n ++;
        lent --;
    }
    puts("");

    // Print steps of calculations
    // from right, each digit of second number multiplied to first number
    for (int i=0; i<L2; i++)
    {
        for (int j=0; j<2*L1; j++)
        printf("%d", step[i][j]);
        puts(""); // Goes to the next line - i++
    }
    puts("______________________________________________________________________");

    // Sum of steps
    carry = 0;
    for (int i=2*L1-1; i>=0; i--) // F\Starting from right digit of each line
    {
        for (int j=0; j<L2; j++) // Starting from first line
        {
            summ = summ + carry + step[j][i];
            carry=0; // In each column Carry should be added to summ for once.
        }

        if (summ >= 10)
        {
            carry = summ / 10;
            result[i] = summ % 10;
        }

        else
        {
            carry = 0;
            result[i] = summ ;
        }
        summ = 0;
    }

    // Print the result
    printf("The answer is:\n");
    int flag1=0;
    for(int i=0; i<2*L1; i++)
    { //To remove redundant zeros at the beginning of the number
        if (result[i] == 0 && flag1 == 0)
            continue;
        else
        {
            printf("%d", result[i]);
            flag1 =1; // Wherever the numbers began, this should capture them.
        }

    }
    // if the result is zero or flag1=0
    if (flag1 == 0)
        printf("0");

   // return 0;
}