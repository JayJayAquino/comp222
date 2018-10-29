
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

   /** Initializing the global variables */
   int MaxLength;
   int length;
   int parity;
   // Initialize the hamming string with a random or NULL memory address
   char *HammingString=NULL;

   /** Function to enter the values */
   void EnterParameters(int *length, int *parity)
   {
       printf("Enter the maximum length: ");
       /** %d reads an integer to be stored in an int. This integer can be signed */
       scanf("%d", length);
       printf("Enter the parity (0=even, 1=odd): ");
       /** %d reads an integer to be stored in an int. This integer can be signed */
       scanf("%d", parity);
   }

   void CheckHamming(char *HammingString, int parity)
   {
       // Initializing the local variables i, j, k, start, length, ParityNumber
       int i, j, k, start, length, ParityNumber;
       printf("Enter the Hamming code: ");
       scanf("%s", HammingString);

       int ErrorBit = 0;                        // Initialize the error bit
       length = strlen(HammingString);          // The strlen computes the length of a string up to, but not including the terminating null character
       length--;
       if (length > MaxLength)
       {
           printf("\n** Invalid Entry - Exceeds Maximum Code Length of %d\n\n", MaxLength);
           return;
       }
       ParityNumber = ceil(log(length)/log(2)); // The ceil function returns the smallest integer that is greater than or equal to 'x'.

       for(i = 1 ; i <= length ; i*=2)
       {
           // pow returns x raised to the power y. In this case, 2 raised to the power i.
           start = pow(2, i);
           int ParityCheck = parity;

           for(j = i; j <= length; j += (i*2))
           {
               for(k = j; (k < i+j) && (k <= length); k++)
               {
                   ParityCheck ^= (HammingString[length - k] - '0');
               } // End the k for-loop
           } // End the j for-loop

               ErrorBit = ErrorBit + (ParityCheck * i);
           } // End the i for-loop

       if(ErrorBit == 0)
       {
           printf("No error \n");
       }
       else
       {
           printf("There is an error in bit: %d\n", ErrorBit);
           if(HammingString[length - ErrorBit] == '0')
           {
               HammingString[length - ErrorBit] = '1';
           }
           else
           {
               HammingString[length - ErrorBit] = '0';
           }

           printf("The corrected Hamming code is: %s \n", HammingString);
       }
   } // End CheckHamming

   int main()
   {

       int parity;
       int choice = 0;
           printf("Error detection/correction: \n");
           printf("----------------------------\n");
           printf("1) Enter parameters \n");
           printf("2) Check Hamming code \n");
           printf("3) Exit \n");
           printf("\nEnter selection: ");
           scanf("%d", &choice);

           while (choice != 3)
           {
               if (choice == 1)
               {
                   EnterParameters(&MaxLength, &parity);
                   HammingString = (char*) malloc (MaxLength * sizeof(char));
                   main();
               }
               else if (choice == 2)
               {
                   CheckHamming(HammingString, parity);
                   main();
               }
               else
               {
                   printf("Valid options are 1, 2, or 3. Quitting program. \n");
                   exit(0);
               }
           }//end while
           exit(0);
   }//end main
