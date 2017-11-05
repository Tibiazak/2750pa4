/*
 * Joshua Bearden
 * CS2750 PA4
 * 04/11/17
 */

#include <stdio.h>
// A struct of account type, holding name, account number and balance
typedef struct account_t{
   char fName[20];
   char initial[2];
   char lName[20];
   int accountNum;
   int accountBal;
} account_t;

int menu()
{
   int status;
   printf("Welcome to the bank!\nPlease make a selection:\n");
   printf("0: Exit\n1: Deposit\n2: Withdrawal\n3: Add Account\n");
   prinf("4: Remove Account\n5: Balance Inquiry\n6: View Accounts\n");
   scanf("%i", status);
   return status;
}

// A menu-driven banking program storing data in a binary file
int main(int argc, char** argv)
{
   //declare variables and open the file
   FILE * fp;
   account_t account;
   account_t accList[49];
   int temp_accNum;
   int temp_amt;
   int readCheck;
   int i = 0;
   int numOfAccts = 0;
   fp = fopen("accounts.dat", "ab+");
   if(fp == NULL)
   {
      printf("Failed to open the file!\n");
      return 1;
   }

   //make an array of everything in the file so far
   readCheck = fread(&account, sizeof(account_t), 1, fp);
   while( (readCheck != 0) && (i < 50) )
   {
      accList[i] = account;
      i++;
      readCheck = fread(&account, sizeof(account_t), 1, fp);
   }
   numOfAccts = i; //get the current max number of accounts

   //start the main loop
   //print menu, get user selection
   int status = menu();
   //exit program on 0
   while(status != 0)
   {
      switch(status) //switch on the option chosen
      {
         case 1: //deposit
            printf("Please enter the account number:\n");
            scanf("%i", temp_accNum);
            for( i = 0; i <= numOfAccts; i++)
            {
               if (accList[i].accountNum == temp_accNum)
               {
                  printf("Please enter the amount to deposit\n");
                  scanf("%i", temp_amt);
                  accList[i].accountBal = temp_amt;
                  printf("Deposit successful!\n");
                  status = menu();
                  break;
               }
            }
            printf("Account number is invalid!\n");
            status = menu();
            break;
         case 2: //withdraw
            status = menu();
            break;
         case 3: //add account
            status = menu();
            break;
         case 4: //remove account
            status = menu();
            break;
         case 5: //balance inquiry
            status = menu();
            break;
         case 6: //view all accounts
            status = menu();
            break;
         default:
            printf("Invalid selection!");
            status = menu();
      }
   }
   fclose(fp);
   return 0;
}