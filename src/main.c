/**
 * Author:    ata babaei   ata.abishka@gmail.com
 * Created:   02.05.2021
 * 
 * https://github.com/abishka/multiply-and-divide-two-large-numbers-in-c
 * 
 * maktabkhoone c learneang prject
 * master:  mr anvari 
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXL 50

//Function
void multiplication();
void clrscr();

int main()
{
    int ch;

    while (1)
    {
        printf("\n\n\n*************** actions ***************\n\n");

        printf("1. Multiplication\n");
        printf("2. Division\n");
        printf("0. Exit\n\n");

        puts("**********************************************");

        printf("Please choose an action: ");
        scanf(" %d", &ch);

        switch (ch)
        {
        case 1:
            multiplication();

            break;

        case 2:

            break;

        case 0:
            return 0;
            break;
        }
    }

    return 0;
}

void multiplication()
{
    char n1[MAXL + 1]; // Plus one is for null operator!
    memset(n1, 0, MAXL * sizeof(char));
    char n2[MAXL + 1];
    memset(n2, 0, MAXL * sizeof(char));

    printf("**************************    multiplication   ****************************\n");

    puts("Please enter the first number:");
    scanf(" %s", n1);
    puts("Please enter the second number:");
    scanf(" %s", n2);

    // Length of numbers
    int L1 = strlen(n1);
    int L2 = strlen(n2);

    // Put the longer number first
    char temp[MAXL + 1];
    if (L1 < L2)
    {
        strcpy(temp, n1);
        strcpy(n1, n2);
        strcpy(n2, temp);
        L1 = strlen(n1);
        L2 = strlen(n2);
    }

    int lent = 2 * L1; // The resultant number length is at most 2 times the first number.
    int carry = 0, summ = 0;

    int step[L2][lent];
    memset(step, 0, L2 * lent * sizeof(int));
    // answer will be stored in result
    int result[lent];
    memset(result, 0, lent * sizeof(int));

    clrscr();

    // print first number
    for (int i = 0; i < (lent - L1) + 2; i++)
        printf(" ");
    printf("%s\n", n1);

    // print second number
    printf("X ");
    for (int i = 0; i < (lent - L2); i++)
        printf(" ");
    printf("%s\n", n2);

    // print _____________ underline
    for (int i = 0; i < (lent + 2); i++)
        printf("_");

    // String of numbers to integer numbers
    int num1[L1];
    int num2[L2];
    for (int i = 0; i < L1; i++)
    {
        if (n1[i] < '0' || n1[i] > '9')
        {
            printf("\n\n\n ############ ERROR INPUT NUMBERS ###########");
            exit(1);
        }

        num1[i] = n1[i] - '0'; // Converts char to integer
    }
    for (int i = 0; i < L2; i++)
    {
        if (n2[i] < '0' || n1[i] > '9')
        {
            printf("\n\n\n ############ ERROR INPUT NUMBERS ###########");
            exit(1);
        }
        num2[i] = n2[i] - '0'; // Converts char to integer
    }

    // Multiplication by algorithm.
    int l2_lent = lent;
    int n = 0, m;
    for (int i = L2 - 1; i >= 0; i--)
    {
        m = l2_lent - 1;
        for (int j = L1 - 1; j >= 0; j--)
        {
            step[n][m] = (carry + (num2[i] * num1[j])) % 10;
            carry = (carry + num2[i] * num1[j]) / 10;
            m--;

            if (m == l2_lent - L1 - 1 && carry != 0) // L1 digits are passed. is there still carry? if yes insert it.
            {
                step[n][m] = carry;
                carry = 0;
            }
        }
        n++;
        l2_lent--;
    }

    puts("\n");

    // Print steps of calculations
    // from right, each digit of second number multiplied to first number
    for (int i = 0; i < L2; i++)
    {
        printf("  ");
        for (int j = 0; j < lent; j++)
            printf("%d", step[i][j]);

        puts(""); // Goes to the next line - i++
    }

    // Sum of steps
    carry = 0;
    for (int i = lent - 1; i >= 0; i--) // F\Starting from right digit of each line
    {
        for (int j = 0; j < L2; j++) // Starting from first line
        {
            summ = summ + carry + step[j][i];
            carry = 0; // In each column Carry should be added to summ for once.
        }

        if (summ >= 10)
        {
            carry = summ / 10;
            result[i] = summ % 10;
        }

        else
        {
            carry = 0;
            result[i] = summ;
        }
        summ = 0;
    }

    //print + _________
    puts("+");
    for (int i = 0; i < (lent + 2); i++)
        printf("_");

    // **************************Print the result
    printf("\n= ");
    int flag1 = 0;
    for (int i = 0; i < lent; i++)
    { //To remove redundant zeros at the beginning of the number
        if (result[i] == 0 && flag1 == 0)
            printf(" ");
        else
        {
            printf("%d", result[i]);
            flag1 = 1; // Wherever the numbers began, this should capture them.
        }
    }
}

void clrscr(void)
{
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}
