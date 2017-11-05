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

// A menu-driven banking program storing data in a binary file
int main(int argc, char** argv)
{
   FILE * fp;
   account_t account;
   int accNumber = 0;
   int amount = 0;
   int readCheck;
   fp = fopen("accounts.dat", "ab+");
   if(fp == NULL)
   {
      printf("Failed to open the file!\n");
      return 1;
   }
   int status = menu();
   while(status != 0)
   {
      switch(status)
      {
         case 1: //deposit
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
      }
   }
   fclose(fp);
}