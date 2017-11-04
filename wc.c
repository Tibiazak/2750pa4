/*
 *Joshua Bearden
 *CS2750 PA4
 *04/11/17
 */
#include <stdio.h>
#include <ctype.h>

//A function that counts words, sentences and characters in a file
void fileCounts(FILE * fp)
{
   bool newWord = true;
   bool newSent = true;
   int charCount = 0;
   int wordCount = 0;
   int sentCount = 0;
   char c = fgetc(fp);
   while(c != EOF)
   {
      if(isspace(c))
      {
         newWord = true;
         if(c == '\n')
         {
            sentCount = true;
         }
      }
      else
      {
         charCount++;
         if(newWord)
         {
            wordCount++;
            newWord = false;
         }
         if(newSent)
         {
            sentCount++;
            newSent = false;
         }
      }
      c = fgetc(fp);
   }
   printf("Number of characters: %i\nNumber of words: %i\nNumber of sentences: %i\n", charCount, wordCount, sentCount);
}

//A program to count the number of words, sentences, and characters
//in a file or from stdio
int main(int argc, char** argv)
{
   int i;
   if(argc > 1)
   {
      // use a file
      FILE *fp;
      for(i=1; i < argc; i++)
      {
         fp = fopen(argv[i], "r");
         fileCounts(fp);
         fclose(fp);
      }
   }
   else
   {
      // process from stdio
      printf("Use standard input.\n");
      fileCounts(stdin);
   }
   return 0;
}