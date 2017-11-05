/*
 * Joshua Bearden
 * CS2750 PA4
 * 04/11/17
 */

#include <stdio.h>
#include <stdbool.h>

// A struct of account type, holding name, account number and balance
typedef struct account_t{
   char fName[20];
   char initial[2];
   char lName[20];
   int accountNum;
   int accountBal;
} account_t;

//Print out the menu and get the user's choice
int menu()
{
   int status = 0;
   printf("\n************************\n");
   printf("Welcome to the bank!\n************************\nPlease make a selection:\n");
   printf("0: Exit\n1: Deposit\n2: Withdrawal\n3: Add Account\n");
   printf("4: Remove Account\n5: Balance Inquiry\n6: View Accounts\n");
   scanf("%d", &status);
   return status;
}

//Write the array to the file
void fileWrite(account_t list[49], int maxNum)
{
   FILE * fp = fopen("accounts.dat", "wb");
   int i;
   for(i = 0; i < maxNum; i++)
   {
      fwrite(&list[i], sizeof(account_t), 1, fp);
   }
   fflush(fp);
   fclose(fp);
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
   bool done = false;
   fp = fopen("accounts.dat", "rb");
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
   fclose(fp);

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
            scanf("%d", &temp_accNum);
            for( i = 0; i < numOfAccts; i++)
            {
               if (accList[i].accountNum == temp_accNum)
               {
                  printf("Please enter the amount to deposit\n");
                  scanf("%d", &temp_amt);
                  accList[i].accountBal = temp_amt;
                  printf("Deposit successful!\n");
                  printf("New balance is: $%d\n", accList[i].accountBal);
                  fileWrite(accList, numOfAccts);
                  done = true;
               }
            }
            if(done)
            {
               done = false;
               status = menu();
               break;
            }
            printf("Account number is invalid!\n");
            status = menu();
            break;
         case 2: //withdraw
            printf("Please enter the account number:\n");
            scanf("%d", &temp_accNum);
            for(i = 0; i < numOfAccts; i++)
            {
               if(accList[i].accountNum == temp_accNum)
               {
                  printf("Please enter the amount to withdraw\n");
                  scanf("%d", &temp_amt);
                  if(accList[i].accountBal > temp_amt)
                  {
                     accList[i].accountBal = temp_amt;
                     printf("The new balance is $%d\n", accList[i].accountBal);
                  }
                  else
                  {
                     printf("Insufficient funds!\n");
                  }
                  done = true;
               }
            }
            if(done)
            {
               done = false;
               fileWrite(accList, numOfAccts);
               status = menu();
               break;
            }
            printf("The account number is invalid!\n");
            status = menu();
            break;
         case 3: //add account
            printf("Please enter the first name:\n");
            scanf("%s", &account.fName[0]);

            printf("Please enter the middle initial:\n");
            scanf("%s", &account.initial[0]);

            printf("Please enter the last name:\n");
            scanf("%s", &account.lName[0]);

            printf("Please enter the desired account number:\n");
            scanf("%d", &temp_accNum);

            if(numOfAccts != 0)
            {
               for(i = 0; i < numOfAccts; i++)
               {
                  if(accList[i].accountNum == temp_accNum)
                  {
                     printf("The account number is in use!");
                     done = true;
                  }
               }
	       if((temp_accNum < 100000) || (temp_accNum > 999999))
	       {
                  printf("The account number must be 6 digits long with no leading zeroes!\n");
		  done = true;
	       }
            }
            if(done)
            {
               done = false;
               status = menu();
               break;
            }
            printf("Please enter the initial deposit amount:\n");
            scanf("%d", &account.accountBal);
            account.accountNum = temp_accNum;

            accList[numOfAccts] = account;
            numOfAccts++;
            printf("Account added successfully!\n");
            fileWrite(accList, numOfAccts);
            status = menu();
            break;
         case 4: //remove account
            printf("Please enter the account number to remove: \n");
            scanf("%d", &temp_accNum);

            for(i = 0; i < numOfAccts; i++)
            {  // if account number exists, overwrite account to be deleted
               // with last account in array
               if(accList[i].accountNum == temp_accNum)
               {
                  accList[i] = accList[numOfAccts-1];
                  numOfAccts--;
                  i = numOfAccts;
                  done = true;
               }
            }
            if(done)
            {
               fileWrite(accList, numOfAccts);
               done = false;
               status = menu();
               break;
            }
            printf("Account number invalid\n");
            status = menu();
            break;
         case 5: //balance inquiry
            printf("Please enter the account number:\n");
            scanf("%d", &temp_accNum);
            for(i = 0; i < numOfAccts; i++)
            {
               if(accList[i].accountNum == temp_accNum)
               {
                  printf("The account in the name of %s %s %s with number %d has a balance of $%d\n", 
                     accList[i].fName, 
                     accList[i].initial, 
                     accList[i].lName, 
                     accList[i].accountNum, 
                     accList[i].accountBal);
                  done = true;
               }
            }
            if(done)
            {
               done = false;
               status = menu();
               break;
            }
            printf("The account number is invalid!\n");
            status = menu();
            break;
         case 6: //view all accounts
            if (numOfAccts == 0)
            {
               printf("There are no accounts!\n");
            }
            for(i = 0; i < numOfAccts; i++)
            {
               printf("Name: %s %s %s\nAccount Number: %d\nBalance: $%d\n\n", 
                     accList[i].fName, 
                     accList[i].initial, 
                     accList[i].lName, 
                     accList[i].accountNum, 
                     accList[i].accountBal);
            }
            status = menu();
            break;
         default:
            printf("Invalid selection!");
            status = menu();
      }
   }
   return 0;
}
